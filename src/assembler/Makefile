CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
SOURCES = assemble.c fileread.c symbol_table.c translation.c assembler_utils.c output.c ../bitutils.c

all: assemble

assemble: $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -lm -o ../assemble

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
