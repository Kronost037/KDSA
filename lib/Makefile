# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -I ../include
PICFLAGS = -fPIC      # needed for shared objects

# Linker flags
LDFLAGS = -shared

# Output
TARGET_LIB = liblist.so

# Sources and objects
SRCS = ./list.c
OBJS = list.o

.PHONY: all clean

all: $(TARGET_LIB)

# Link object into shared library
$(TARGET_LIB): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET_LIB)

# Compile source into position-independent object file
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(PICFLAGS) -c $(SRCS) -o $(OBJS)

clean:
	$(RM) $(OBJS) $(TARGET_LIB)
