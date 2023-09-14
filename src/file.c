#include "../include/file.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *path, enum READ_MODE mode) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Determine the file size to allocate the correct amount of memory
  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET);

  // If in WITH_SPACES mode, add 1 byte for every 5 characters
  if (mode == WITH_SPACES) {
    fsize += fsize / 5;
  }

  // Create the buffer to store the file contents
  char *fcontent = malloc(fsize + 1);

  // Read the file into the buffer, adding spaces every 5 characters
  for (int i = 0; i < fsize; i++) {
    // TODO - Fix improper spacing when reading files
    /* if (i > 0 && mode == WITH_SPACES && i % 5 == 0) { */
    /*   fcontent[i] = ' '; */
    /* } else { */
    fread(&fcontent[i], 1, 1, file);
    /* } */
  }

  fclose(file);
  return fcontent;
}
