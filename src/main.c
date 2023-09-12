#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file.h"
#include "../include/shift_cipher.h"

#define SHIFT_DISP "Shift: %d\n"
#define CONTROLS_DISP "Press J/K to shift the text, Q to quit"

void draw_text(WINDOW *win, char *text, int r, int c) {
  int width, height;
  getmaxyx(win, height, width);

  int line = 0;
  long text_len = strlen(text);
  for (long text_pos = 0; text_pos < text_len; text_pos++) {
    if (text[text_pos] == '\n' || text_pos != 0 && text_pos % width == 0) {
      line++;
      continue;
    }

    mvwaddch(win, r + line, c + text_pos % width, text[text_pos]);
  }
}

void redraw_screen(char *file, int shift, WINDOW *cipher_pane) {
  clear();
  printw(SHIFT_DISP, shift);
  mvprintw(1, 0, "%s", CONTROLS_DISP);

  draw_text(cipher_pane, shift_cipher(file, shift, ENCIPHER), 0, 0);
  box(cipher_pane, 0, 0);

  refresh();
  wrefresh(cipher_pane);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *file = read_file(argv[1]);
  if (file == NULL) {
    perror("Error reading file!\n");
    return EXIT_FAILURE;
  }

  int shift = 0, quit = 0;

  initscr();
  curs_set(0);

  int rows, columns;
  getmaxyx(stdscr, rows, columns);
  WINDOW *cipher_pane = newwin(rows - 3, columns, 3, 0);
  if (cipher_pane == NULL) {
    free(file);
    curs_set(1);
    endwin();
    perror("Error creating window!\n");
    return EXIT_FAILURE;
  }

  while (!quit) {
    redraw_screen(file, shift, cipher_pane);
    char in = getch();

    switch (in) {
    case 'j':
      // Subtract 1 from shift, wraparound to 25
      shift = shift == 0 ? 25 : shift - 1;
      break;
    case 'k':
      // Add 1 to shift, wraparound to 0
      shift = (shift + 1) % 26;
      break;
    case 'q':
      quit = 1;
      break;
    default:
      break;
    }
  }

  // Free the file buffer and end curses
  free(file);
  delwin(cipher_pane);
  curs_set(1);
  endwin();
  return EXIT_SUCCESS;
}
