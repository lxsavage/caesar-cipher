EXEC_NAME=shift-cipher
CC=clang
CC_LINK_FLAG=-lncurses
CC_FLAG=-Wall

H_FILES=include/shift_cipher.h include/file.h
SRC_FILES=src/main.c src/shift_cipher.c src/file.c
OBJ_FILES=$(SRC_FILES:src/%.c=obj/%.o)

all: dist/$(EXEC_NAME)

clean:
	rm -r obj/ dist/ 2>/dev/null || true

dist/$(EXEC_NAME): $(OBJ_FILES)
	mkdir -p dist/
	$(CC) $(CC_LINK_FLAG) -o $@ $^

obj/%.o: src/%.c $(H_FILES)
	mkdir -p obj/
	$(CC) $(CC_FLAG) -c $< -o $@
