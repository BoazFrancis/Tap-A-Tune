CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic -Lsdl/lib64 -lSDL_mixer -lSDL -lpthread -lm -ldl -lpthread -Isdl/include/SDL
OBJS = ctap.o draw.o init.o utils.o play_sound.o read_file.o events.o song.o
GTK = `pkg-config --libs --cflags gtk+-2.0`

all: extension

# Make every object file from its individual .c source file
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(GTK)

# Link all the object files together to get the full binary game
extension: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -o ../../bin/extension $(GTK)
