CC           = gcc
CFLAGS       = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
SDL_CFLAGS   = $(shell sdl2-config --libs --cflags)
SDL_LDFLAGS  = $(shell sdl2-config --libs)
main_objects = main.o controller.o game.o graphics.o levels.o palette.o

.SUFFIXES: .c .o

.PHONY: clean

main: $(main_objects)
	$(CC) $(SDL_CFLAGS) $(CFLAGS) $(main_objects) -o main

$(main_objects): includes.h

.c.o:
	$(CC) $(CFLAGS) $(SDL_LDFLAGS) -c $<


clean:
	rm -f $(wildcard *.o)
	rm -f main
