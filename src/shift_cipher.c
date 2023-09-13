#include "../include/shift_cipher.h"
#include <stdio.h>
#include <string.h>

void shift_cipher(const char *message, char *out, int shift,
                  enum SHIFT_MODE mode) {
  out = memcpy(out, message, strlen(message) + 1);
  if (sizeof(message) != sizeof(out)) {
    perror("message and out must be the same size");
    return;
  }

  // Find the offset for the shift
  int offset = shift;
  if (mode == DECIPHER) {
    offset = 26 - shift;
  }

  for (int i = 0; out[i] != '\0'; i++) {
    // Uppercase: 65 - 90
    if (out[i] >= 65 && out[i] <= 90) {
      char capital_index = out[i] - 65;
      out[i] = (capital_index + offset) % 26 + 97;
    } else if (out[i] >= 97 && out[i] <= 122) {
      char lowercase_index = out[i] - 97;
      out[i] = (lowercase_index + offset) % 26 + 97;
    }
  }
}
