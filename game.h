#ifndef __GAME_H
#define __GAME_H

typedef enum game_state {
    START_GAME, START_MENU, PLAY_GAME, PAUSE_SCREEN, LOSE_GAME, GAME_OVER, WIN_LEVEL, WIN_GAME
} game_state_t;

typedef struct {
    double x;
    double y;
    double dx;
    double dy;
    double radius;
} ball_t;

typedef struct {
    double x;
    double y;
    double dx;
    double width;
    int8_t level; //will also hold the level you are at
    int8_t lives;
} bar_t;

void init_bar(bar_t *bar);
void reset_bar(bar_t *bar);
void init_ball(ball_t * ball);
void reset_ball(ball_t * ball);
void update_bar(bar_t *bar, int8_t controller_state);
void update_ball(ball_t *ball, bar_t *bar, game_state_t *game_state);
void update_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state);
void lose_life(bar_t *bar, game_state_t *game_state);

#endif // __GAME_H
