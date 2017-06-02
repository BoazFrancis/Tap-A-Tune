CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
SOURCES = emulate.c fetchcycle.c ../bitutils.c binaryread.c data_processing.c data_processing_utils.c multiply.c branch.c output.c single_data_transfer.c

all: emulate

emulate: $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -lm -o ../emulate

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
