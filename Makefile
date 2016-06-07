CC           = gcc
CFLAGS       = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
SDL_CFLAGS   = $(shell sdl2-config --libs --cflags)
SDL_LDFLAGS  = $(shell sdl2-config --libs)
SDL_MIXER_LDFLAGS = $(shell sdl-config --cflags)
SDL_MIXER_CFLAGS = $(shell sdl-config --libs) 
main_objects = main.o controller.o game.o graphics.o levels.o palette.o cheat.o sound.o

.SUFFIXES: .c .o

.PHONY: clean

main: $(main_objects)
	$(CC) -o main $(main_objects) $(SDL_CFLAGS) $(CFLAGS) $(SDL_MIXER_CFLAGS) -lSDL2_mixer -lSDL2_ttf

$(main_objects): includes.h

.c.o:
	$(CC) $(CFLAGS) $(SDL_LDFLAGS) -c $(SDL_MIXER_LDFLAGS) $<


clean:
	rm -f $(wildcard *.o)
	rm -f main
