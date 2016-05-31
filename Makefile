CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
main_objects = main.o controller.o game.o graphics.o levels.o palette.o

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: $(main_objects)
	$(CC) -o main $(CFLAGS) $(main_objects)

$(main_objects): includes.h

clean:
	rm -f $(wildcard *.o)
	rm -f main
