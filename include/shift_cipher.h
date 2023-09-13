#ifndef SHIFT_CIPHER_H
#define SHIFT_CIPHER_H

enum SHIFT_MODE { ENCIPHER, DECIPHER };

/**
 * Shift a message using a Caesar cipher.
 * @param message The message to shift.
 * @param out The output buffer.
 * @param shift The number of characters to shift.
 * @param mode The mode of the cipher (encipher or decipher).
 */
void shift_cipher(const char *message, char *out, int shift,
                  enum SHIFT_MODE mode);

#endif
