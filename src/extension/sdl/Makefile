CC      = gcc
SOURCES = SDLTest.c

all: sdl

sdl: $(SOURCES)
	$(CC) -Iinclude/SDL $(SOURCES) -Llib64 -lSDL -lpthread -lm -ldl -lpthread -o SDLTest
