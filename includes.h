#ifndef __INCLUDES_H
#define __INCLUDES_H

/*
 * C standard library
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "SDL2/SDL.h"

/*
 * Header files
 */
#include "levels.h"
#include "palette.h"
#include "controller.h"
#include "game.h"
#include "graphics.h"
#include "main.h"

/*
 * Useful Macros and defines
 */
#define BRICKS_PER_LEVEL 150
#define BRICK_WIDTH 50
#define BRICK_HEIGHT 14
#define BRICKS_PER_ROW 10
#define BAR_R 0x12
#define BAR_G 0xFA
#define BAR_B 0xA4
#define BAR_A 0x00
#define BALL_R 0x11
#define BALL_G 0x45
#define BALL_B 0xB3
#define BALL_A 0x01
#define BACK_R 0x00
#define BACK_G 0x00
#define BACK_B 0x00
#define BACK_A 0x01
#define BAR_COLOUR 0x12FAA4
#define BALL_COLOUR 0x1145B3
#define BACK_COLOUR 0x000000
#define EIGHTBIT_MASK 0xFF

#endif //__INCLUDES_H
