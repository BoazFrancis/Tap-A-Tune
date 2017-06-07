CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

SOURCES = graphics.c favicon.c button.c toolbar.c dialog.c

all: gui

gui: $(H) $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -o gui `pkg-config --libs --cflags gtk+-2.0`

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
