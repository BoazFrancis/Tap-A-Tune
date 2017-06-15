CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

DEPS = emulate.h ../lib/defs.h ../lib/bitutils.h
OBJS = emulate.o binary_read.o branch.o data_processing.o utils.o fetch_cycle.o multiply.o output.o single_data_transfer.o gpio.o ../lib/bitutils.o

all: emulate

# Make every object file from its individual .c source file
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Link all the object files together to get the full binary emulator file
emulate: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)  -lm -o ../../bin/emulate
