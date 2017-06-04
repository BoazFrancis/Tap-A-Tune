CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

H = emulate.h ../lib/defs.h ../lib/bitutils.h
SOURCES = emulate.c binaryread.c branch.c data_processing.c data_processing_utils.c fetchcycle.c multiply.c output.c single_data_transfer.c ../lib/bitutils.c

all: emulate

emulate: $(H) $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -lm -o ../../bin/emulate

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
