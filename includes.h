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
#include "palette.h"
#include "controller.h"
#include "game.h"
#include "graphics.h"
#include "levels.h"
#include "main.h"

/*
 * Useful Macros and defines
 */
#define MAX_BRICKS_PER_LEVEL 150
#define BRICK_WIDTH 30.0
#define BRICK_HEIGHT 10.0
#define BRICKS_PER_ROW 10
#define BAR_COLOUR 0x99
#define BALL_COLOUR 0XFD
#define BAR_R 0x12
#define BAR_G 0xFA
#define BAR_B 0xA4
#define BAR_A 0x00
#define BALL_R 0x11
#define BALL_G 0x45
#define BALL_B 0xB3
#define BALL_A 0x00
#define BACK_R 0x69
#define BACK_G 0x45
#define BACK_B 0x00
#define BACK_A 0x00
#define EIGHTBIT_MASK 0xFF

#endif //__INCLUDES_H
