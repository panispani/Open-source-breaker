#include "includes.h"
#define START_LIVES 3
#define DISPLACEMENT 5
#define MAX_BAR_SPEED 15
#define DEF_BAR_WIDTH 50
#define DEF_BALL_RADIUS 4
#define DEF_BALL_HEIGHT (2 * gameheight / 3)
#define DEF_BAR_HEIGHT (15 * gameheight / 16);
#define DEF_BALL_DX 1
#define DEF_BALL_DY 1

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
    bar->y = DEF_BAR_HEIGHT;
    bar->dx = 0;
    bar->width = DEF_BAR_WIDTH;
}

void init_ball(ball_t *ball) {
    reset_ball(ball);
}

void reset_ball(ball_t * ball) {
    ball->x = gamewidth / 2;
    ball->y = DEF_BALL_HEIGHT;
    ball->dx = DEF_BALL_DX;
    ball->dy = DEF_BALL_DY;
    ball->radius = DEF_BALL_RADIUS;
}

/*
 * Update the bar position according to the buttons pressed
 * TODO: fire from the bar
 */
void update_bar(bar_t *bar, int8_t controller_state) {
    bar->dx = cram((controller_state & 0x1) - (controller_state & 0x2) + bar->dx, -MAX_BAR_SPEED, MAX_BAR_SPEED);
    bar->x = cram(bar->x + bar->dx, 0 + bar->width, gamewidth - bar->width);
}

/*
 * Given left and right limits make sure x is not out of bounds,
 * if this is the case place it on the nearest bound
 */ 
double cram(double x, double left, double right) {
    if (left > right) {
        double temp = left;
        right = left;
        left = temp;
    }
    return x < left ? left : (x > right ? right : x);
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
void update_ball(ball_t *ball, bar_t *bar, game_state_t *game_state) {
    //update ball
    ball->x += ball->dx;
    ball->y += ball->dy;
    ball->x = cram(ball->x, 0 + ball->radius, gamewidth  - ball->radius);
    ball->y = cram(ball->y, 0 + ball->radius, gameheight - ball->radius);

    //check if lost
    if(ball->y < 0) { //or bar->y
        *game_state = LOSE_GAME;
        return;
    }
    //check for collisions with the bar
}

void update_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state) {
    //check for collisions with bricks
    for(int i = 0; i < MAX_BRICKS_PER_LEVEL; i++) {
        if(bricks[i]) {
            if(collision(ball, center_of_brick(i) ,BRICK_WIDTH, BRICK_HEIGHT)) {
                bricks[i] = 0x0;

            }
        }
    }


}
