CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

all:
	+$(MAKE) -C src/emulator
	+$(MAKE) -C src/assembler
