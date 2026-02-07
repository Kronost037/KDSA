CC = gcc
CFLAGS = -Wall -Wextra -I../include
LDFLAGS = -L../lib -llist -Wl,-rpath,'$$ORIGIN/../'

SRC = example1.c

example1: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o example1 $(LDFLAGS)
clean:
	rm example1
