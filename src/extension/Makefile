CC      = gcc

all: sound gui

SOUND_SOURCES = sound2.c play_sound.c
sound: $(SOUND_SOURCES)
	$(CC) -Isdl/include/SDL $(SOUND_SOURCES) -Lsdl/lib64 -lSDL_mixer -lSDL -lpthread -lm -ldl -lpthread -o bin/sound2

GUI_SOURCES = graphics.c exit.c text.c keypress.c favicon.c
gui: $(GUI_SOURCES)
	$(CC) $(CFLAG) $(GUI_SOURCES) -o bin/gui `pkg-config --libs --cflags gtk+-2.0`
