#ifndef __PALETTE_H
#define __PALETTE_H
#define PALETTE_COLOURS 16

/* GAME COLOURS */
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
#define BACK_COLOUR 0x292929

/* PALETTE INDICES */
#define RED 11
#define BLUE 13
#define YELLOW 14
#define GREEN 12
#define PURPLE 15
#define WHITE 7


extern uint32_t palette[PALETTE_COLOURS];

#endif //__PALETTE_H
