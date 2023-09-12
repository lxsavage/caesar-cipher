#include "../include/file.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Determine the file size to allocate the correct amount of memory
  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Create the buffer and read the file into it (ends with an EOF character)
  char *fcontent = malloc(fsize + 1);
  fread(fcontent, 1, fsize, file);

  fclose(file);
  return fcontent;
}
