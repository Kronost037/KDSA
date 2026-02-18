CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include
LDFLAGS = -L../lib -llist -Wl,-rpath,'$$ORIGIN/../lib'

SRC = example1.c

.PHONY: clean example1

example1: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o example1 $(LDFLAGS)
clean:
	rm example1
