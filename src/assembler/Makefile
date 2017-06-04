CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

H = assemble.h ../lib/defs.h ../lib/bitutils.h
SOURCES = assemble.c fileread.c symbol_table.c translation.c assembler_utils.c map.c output.c ../lib/bitutils.c

all: assemble

assemble: $(H) $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -lm -o ../../bin/assemble

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
