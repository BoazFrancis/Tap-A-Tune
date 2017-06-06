CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

H = assemble.h ../lib/defs.h ../lib/bitutils.h

SOURCES = assemble.c read_file.c symbol_table.c translation.c data_processing.c data_processing_utils.c map.c output.c utils.c branch.c multiply.c special.c single_data_transfer.c single_data_transfer_utils.c ../lib/bitutils.c


all: assemble

assemble: $(H) $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -lm -o ../../bin/assemble

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
