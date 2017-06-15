CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

DEPS = assemble.h ../lib/defs.h ../lib/bitutils.h
OBJS = assemble.o read_file.o symbol_table.o translation.o data_processing.o data_processing_utils.o map.o output.o utils.o branch.o multiply.o special.o single_data_transfer.o single_data_transfer_utils.o ../lib/bitutils.o

all: assemble

# Make every object file from its individual .c source file
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Link all the object files together to get the full binary assembler file
assemble: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)  -lm -o ../../bin/assemble
