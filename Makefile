# Compiler and flags
CC       = gcc
CFLAGS   = -Wall -Wextra -I./include
PICFLAGS = -fPIC

# Linker flags
LDFLAGS  = -shared

# Directories
SRCDIR   = src
INCDIR   = include
OBJDIR   = obj
LIBDIR   = lib

# Output
TARGET_LIB = $(LIBDIR)/liblist.so

# Sources and objects
SRCS = $(SRCDIR)/list.c
# This automatically changes src/list.c to obj/list.o
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: all clean compile_commands

all: $(TARGET_LIB)

# Link objects into shared library
$(TARGET_LIB): $(OBJS)
	@mkdir -p $(LIBDIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET_LIB)

# Compile source into position-independent object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

# Generate compilation database for Emacs/LSP
compile_commands:
	make clean
	bear -- make all

clean:
	$(RM) -r $(OBJDIR) $(LIBDIR)
	$(RM) compile_commands.json
