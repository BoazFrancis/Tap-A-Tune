CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
SOURCES = assemble.c fileread.c symbol_table.c

all: assemble

assemble: $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -lm -o ../assemble

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
