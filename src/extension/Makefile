CC      = gcc

all: extension

GUI_SOURCES = extension.c buttons.c start_screen.c play_sound.c music.c move.c

extension: $(GUI_SOURCES)
	$(CC) $(CFLAG) -Isdl/include/SDL $(GUI_SOURCES) -Lsdl/lib64 -lSDL_mixer -lSDL -lpthread -lm -ldl -lpthread -o bin/extension `pkg-config --libs --cflags gtk+-2.0`
