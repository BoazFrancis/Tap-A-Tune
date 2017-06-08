CC      = gcc

all: sound

SOUND_SOURCES = music.c ../play_sound.c
sound: $(SOUND_SOURCES)
	$(CC) -I../sdl/include/SDL $(SOUND_SOURCES) -L../sdl/lib64 -lSDL_mixer -lSDL -lpthread -lm -ldl -lpthread -o music

GUI_SOURCES = graphics.c favicon.c exit.c text.c keypress.c
gui: $(GUI_SOURCES)
	$(CC) $(CFLAG) $(GUI_SOURCES) -o gui `pkg-config --libs --cflags gtk+-2.0`
