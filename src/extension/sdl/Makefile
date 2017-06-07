CC      = gcc
SOURCES = sound.c

all: sdl

sdl: $(SOURCES)
	$(CC) -Iinclude/SDL $(SOURCES) -Llib64 -lSDL_mixer -lSDL -lpthread -lm -ldl -lpthread -o sound
