#ifndef __GAME_H
#define __GAME_H

typedef enum game_state {
    START_GAME, START_MENU, PLAY_GAME, PAUSE_SCREEN,
    LOSE_GAME, GAME_OVER, WIN_LEVEL, WIN_GAME
} game_state_t;

typedef enum {
    VERTICAL = 1, HORIZONTAL = 2;
} orientation;

typedef struct {
    double x;
    double y;
} vector2D_t;

typedef struct {
    vector2D_t position;
    vector2D_t direction;
    double diameter;
} ball_t;

typedef struct {
    vector2D_t position;
    vector2D_t direction;
    double width;
    double height;
    int8_t level;
    int8_t lives;
} bar_t;

extern int gamewidth;
extern int gameheight;

void init_bar(bar_t *bar);
void reset_bar(bar_t *bar);
void init_ball(ball_t * ball);
void reset_ball(ball_t * ball);
void update_bar(bar_t *bar, int8_t controller_state);
void update_ball(ball_t *ball, bar_t *bar, game_state_t *game_state);
void update_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state);
void lose_life(bar_t *bar, game_state_t *game_state);
double cram(double x, double left, double right);
vector2D_t center_of_brick(int n);

#endif // __GAME_H
