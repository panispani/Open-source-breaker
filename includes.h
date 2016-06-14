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
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

/*
 * Header files
 */
#include "sound.h"
#include "levels.h"
#include "palette.h"
#include "game.h"
#include "controller.h"
#include "graphics.h"
#include "powerups.h"
#include "main.h"

/*
 * Useful Macros and defines
 */
#define START_LIVES 3
#define BRICKS_PER_LEVEL 572
#define BRICK_WIDTH 25
#define BRICK_HEIGHT 25
#define BRICKS_PER_ROW 26
#define DEF_BALL_RADIUS 4
#define BAR_R 0x12
#define BAR_G 0xFA
#define BAR_B 0xA4
#define BAR_A 0x00
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
#define FLAG_1 0x1
#define FLAG_2 0x2
#define FLAG_3 0x4
/* PALETTE INDICES */
#define RED 11 
#define BLUE 13
#define YELLOW 14
#define GREEN 12
#define PURPLE 15

#endif //__INCLUDES_H
