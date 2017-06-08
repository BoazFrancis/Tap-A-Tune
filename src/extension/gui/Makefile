CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

SOURCES = graphics.c favicon.c exit.c text.c keypress.c

all: gui

gui: $(H) $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -o gui `pkg-config --libs --cflags gtk+-2.0`
