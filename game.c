#include "includes.h"
#define START_LIVES 3

void init_bar(bar_t *bar) {
    bar->x = gamewidth / 2;
    bar->y = 15 * gameheight / 16;
    bar->old_x =  bar->x;
    bar->old_y = bar->y;
    bar->level = 0;
    bar->lives = START_LIVES;
}

void reset_bar(bar_t *bar) {

}

void init_ball(ball_t *ball) {
    ball->x = gamewidth / 2;
    ball->y = 2 * gameheight / 3; 
    ball->old_x = rand() % gamewidth;
    ball->old_y = rand() % gameheight;
}

void reset_ball(ball_t * ball) {

}

void update_bar(bar_t *bar, int8_t controller_state) {

}

void update_ball_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state) {

}

