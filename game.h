#ifndef __GAME_H
#define __GAME_H

typedef enum {
    START_GAME, START_MENU, PLAY_GAME, PAUSE_SCREEN, LOSE_GAME, GAME_OVER, WIN_LEVEL, WIN_GAME
} game_state_t;

typedef struct {
    int32_t x;
    int32_t y;
    int32_t old_x;
    int32_t old_y;
} ball_t;

typedef struct {
    int32_t x;
    int32_t y;
    int32_t old_x;
    int32_t old_y;
} bar_t;









#endif // __GAME_H
