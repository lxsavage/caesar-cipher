# Caesar Cipher Tool

This tool is a basic interactive application that takes in ciphertext (in the
form of a text file) and allows for shifting the letters around to encipher or
deciper a Caesar Cipher.

## Building and Running

This project only depends on the system it's running on supporting NCurses, and
is built by default with clang. These can easily be modified in the Makefile,
but haven't been tested otherwise.

Build the project:

```shell
make
```

Clean a build:

```shell
make clean
```

Run the built project:

```shell
dist/shift-cipher <ciphertext file path>
```
