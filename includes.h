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
#include <linux/fb.h>
#include <sys/mman.h>
#include <unistd.h>
#include "SDL.h"

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

#endif //__INCLUDES_H
