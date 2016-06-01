#include "includes.h"
#define START_LIVES 3
#define DISPLACEMENT 1

void init_bar(bar_t *bar) {
    reset_bar(bar);
    bar->level = 0;
    bar->lives = START_LIVES;
}

void lose_life(bar_t *bar, game_state_t *game_state) {
    bar->lives--;
    if(bar->lives == 0) {
        *game_state = GAME_OVER;
    }
}

void reset_bar(bar_t *bar) {
    bar->x = gamewidth / 2;
    bar->y = 15 * gameheight / 16;
    bar->dx = 0;
    bar->dy = 0;
}

void init_ball(ball_t *ball) {
    reset_ball(ball);
}

void reset_ball(ball_t * ball) {
    ball->x = gamewidth / 2;
    ball->y = 2 * gameheight / 3;
    ball->dx = 0;
    ball->dy = 0;
}

/*
 * Update the bar position according to the buttons pressed
 * TODO: fire from the bar
 */
void update_bar(bar_t *bar, int8_t controller_state) {
    int dx = (controller_state & 0x1) - (controller_state & 0x2);
    bar->x += dx * DISPLACEMENT;
}

double cram(double x, double mn, double mx) {
    if (mn > mx) {
        double temp = mn;
        mx = mn;
        mn = temp;
    }
    return x < mn ? mn : (x > mx ? mx : x);
}

double min(double a, double b) {
    return a > b ? b : a;
}

bool collision(ball_t *ball, double center, double width, double height) {
    return false;
}

double center_of_brick(int n) {
    int row = n / BRICKS_PER_ROW;
    int col = n % BRICKS_PER_ROW;
    double center =
        row * gamewidth + col + BRICK_WIDTH / 2 + BRICK_HEIGHT / 2;
    return center;
}

//TODO: USE DIR NOT OLD/NEW
void update_ball_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state) {
    //update ball
    ball->x += ball->dx;
    ball->y += ball->dy;
    ball->x = cram(ball->x, 0, gamewidth);
    ball->y = cram(ball->y, 0, gameheight);

    //check if lost
    if(ball->y < 0) { //or bar->y
        *game_state = LOSE_GAME;
        return;
    }
    //check for collisions with bricks
    for(int i = 0; i < MAX_BRICKS_PER_LEVEL; i++) {
        if(bricks[i]) {
            if(collision(ball, center_of_brick(i) ,BRICK_WIDTH, BRICK_HEIGHT)) {
                bricks[i] = 0x0;

            }
        }
    }
    //check for collisions with the bar
}


