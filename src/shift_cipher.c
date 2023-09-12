#include "../include/shift_cipher.h"

char *shift_cipher(char *message, int shift, enum SHIFT_MODE mode) {
  int offset = shift;
  if (mode == DECIPHER) {
    offset = 26 - shift;
  }

  for (int i = 0; message[i] != '\0'; i++) {
    if (message[i] >= 'a' && message[i] <= 'z') {
      message[i] = (message[i] - 'a' + offset) % 26 + 'a';
    } else if (message[i] >= 'A' && message[i] <= 'Z') {
      message[i] = (message[i] - 'A' + offset) % 26 + 'A';
    }
  }
  return message;
}
