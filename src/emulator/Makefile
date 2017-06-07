CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

H = emulate.h ../lib/defs.h ../lib/bitutils.h
SOURCES = emulate.c binary_read.c branch.c data_processing.c utils.c fetch_cycle.c multiply.c output.c single_data_transfer.c gpio.c ../lib/bitutils.c

all: emulate

emulate: $(H) $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -lm -o ../../bin/emulate
