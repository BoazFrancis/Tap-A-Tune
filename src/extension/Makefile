CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

all: extension

GUI_SOURCES = ctap.c draw.c init.c utils.c play_sound.c read_file.c events.c song.c

extension: $(GUI_SOURCES)
	$(CC) $(CFLAGS) -Isdl/include/SDL $(GUI_SOURCES) -Lsdl/lib64 -lSDL_mixer -lSDL -lpthread -lm -ldl -lpthread -o bin/extension `pkg-config --libs --cflags gtk+-2.0`
