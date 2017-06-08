CC      = gcc

all: sound gui

SOUND_SOURCES = sound2.c
sound: $(SOUND_SOURCES)
	$(CC) -Isdl/include/SDL $(SOUND_SOURCES) -Lsdl/lib64 -lSDL_mixer -lSDL -lpthread -lm -ldl -lpthread -o sound2

GUI_SOURCES = graphics.c favicon.c exit.c text.c keypress.c
gui: $(GUI_SOURCES)
	$(CC) $(CFLAG) $(GUI_SOURCES) -o gui `pkg-config --libs --cflags gtk+-2.0`
