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
#include <SDL_mixer.h>

/*
 * Header files
 */
#include "sound.h"
#include "levels.h"
#include "palette.h"
#include "controller.h"
#include "game.h"
#include "graphics.h"
#include "main.h"

/*
 * Useful Macros and defines
 */
#define BRICKS_PER_LEVEL 221
#define BRICK_WIDTH 25
#define BRICK_HEIGHT 25
#define BRICKS_PER_ROW 13
#define BAR_R 0x12
#define BAR_G 0xFA
#define BAR_B 0xA4
#define BAR_A 0x00
/*
#define BALL_R 0x11
#define BALL_G 0x45
#define BALL_B 0xB3
#define BALL_A 0x01
*/
#define BALL_R 0xEB
#define BALL_G 0xC8
#define BALL_B 0x57
#define BALL_A 0x01
#define BACK_R 0x29
#define BACK_G 0x29
#define BACK_B 0x29
#define BACK_A 0x01
#define BAR_COLOUR 0x12FAA4
#define BALL_COLOUR 0xEBC867
#define BACK_COLOUR 0x000000
#define EIGHTBIT_MASK 0xFF
/* CONTROLLER FLAGS */
#define A_FLAG 0x1
#define D_FLAG 0x2
#define SPACE_FLAG 0x4


#endif //__INCLUDES_H
