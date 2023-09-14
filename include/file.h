#ifndef FILE_H
#define FILE_H

enum READ_MODE { NORMAL, WITH_SPACES };

/**
 * Read a file and return its content.
 * @param path The path of the file to read.
 * @param mode The mode of reading. NOT YET IMPLEMENTED.
 * @return The content of the file.
 */
char *read_file(char *path, enum READ_MODE mode);

#endif
