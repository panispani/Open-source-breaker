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
    int8_t level; //will also hold the level you are at
} bar_t;

void init_bar(bar_t *bar);
void init_ball(ball_t * ball);
void update_bar(bar_t *bar, int8_t controller_state);
void update_ball_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state);

#endif // __GAME_H
