#ifndef SHIFT_CIPHER_H
#define SHIFT_CIPHER_H

enum SHIFT_MODE { ENCIPHER, DECIPHER };

/**
 * Shift a message using a Caesar cipher.
 * @param message The message to shift.
 * @param shift The number of characters to shift.
 * @param mode The mode of the cipher (encipher or decipher).
 * @return The shifted message.
 */
char *shift_cipher(char *message, int shift, enum SHIFT_MODE mode);

#endif
