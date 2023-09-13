#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file.h"
#include "../include/shift_cipher.h"

#define SHIFT_DISP "Shift: decipher %d, encipher %d\n"
#define CONTROLS_DISP "Press J/K to shift the text, Q to quit"

void draw_text(WINDOW *win, char *text, int r, int c) {
  int rows, columns;
  getmaxyx(win, rows, columns);

  int i = 0;
  for (int row = r; row < rows - 1; row++) {
    for (int col = c; col < columns - 2; col++) {
      if (text[i] == ' ' || text[i] == '\n') {
        i++;
      }
      if (text[i] == '\0') {
        return;
      }

      mvwaddch(win, 1 + row, 1 + col, text[i]);
      i++;
    }
  }
}

void redraw_screen(char *file, char *cipher_buffer, int shift,
                   WINDOW *cipher_pane) {
  clear();
  printw(SHIFT_DISP, shift, 26 - shift);

  shift_cipher(file, cipher_buffer, shift, ENCIPHER);
  mvprintw(1, 0, "%s", CONTROLS_DISP);

  box(cipher_pane, 0, 0);
  draw_text(cipher_pane, cipher_buffer, 0, 0);

  refresh();
  wrefresh(cipher_pane);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *file = read_file(argv[1]);
  char *cipher = malloc(strlen(file) + 1);
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
    redraw_screen(file, cipher, shift, cipher_pane);
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
  free(cipher);
  delwin(cipher_pane);
  curs_set(1);
  endwin();
  return EXIT_SUCCESS;
}
