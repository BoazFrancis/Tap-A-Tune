CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o

emulate: emulate.o fetchcycle.c bitutils.c binaryread.c data_processing.c data_processing_utils.c multiply.c branch.c output.c single_data_transfer.c -lm

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
