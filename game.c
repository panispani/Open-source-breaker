#include "includes.h"
#define START_LIVES 3
#define MAX_BAR_SPEED 15
#define DEF_BAR_WIDTH 50
#define DEF_BAR_HEIGHT 6
#define DEF_BALL_RADIUS 4
#define DEF_BALL_HEIGHT (2 * gameheight / 3)
#define DEF_BAR_Y (15 * gameheight / 16);
#define DEF_BALL_DX 1
#define DEF_BALL_DY 1
#define BAR_SPEED_UP 3

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
    bar->position.x = gamewidth / 2;
    bar->position.y = DEF_BAR_Y;
    bar->direction.x = 0;
    bar->width = DEF_BAR_WIDTH;
    bar->height = DEF_BAR_HEIGHT;
}

void init_ball(ball_t *ball) {
    reset_ball(ball);
}

void reset_ball(ball_t * ball) {
    ball->position.x = gamewidth / 2;
    ball->position.y = DEF_BALL_HEIGHT;
    ball->direction.x = DEF_BALL_DX;
    ball->direction.y = DEF_BALL_DY;
    ball->radius = DEF_BALL_RADIUS;
}

/*
 * Update the bar position according to the buttons pressed
 * TODO: fire from the bar
 */
void update_bar(bar_t *bar, int8_t controller_state) {
    int input = (controller_state & 0x1) - (controller_state & 0x2);
    if (!input) {
        bar->direction.x /= 1.15;
    } else {
        bar->direction.x = cram(input * BAR_SPEED_UP + bar->direction.x, -MAX_BAR_SPEED, MAX_BAR_SPEED);
        bar->position.x = cram(bar->position.x + bar->direction.x, 0 + bar->width, gamewidth - bar->width);
    }
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

//TODO: peter pliz :)
bool collision(ball_t *ball, vector2D_t center, double width, double height) {
    return false;
}

vector2D_t corner_of_brick(int n) {
    vector2D_t corner;
    corner.y = BRICK_HEIGHT * (n / BRICKS_PER_ROW);
    corner.x = BRICK_WIDTH * (n % BRICKS_PER_ROW);
    return corner;
}

void update_ball(ball_t *ball, bar_t *bar, game_state_t *game_state) {
    //update ball
    ball->position.x = cram(ball->position.x + ball->direction.x, 0 + ball->radius, gamewidth  - ball->radius);
    ball->position.y = cram(ball->position.y + ball->direction.y, 0 + ball->radius, gameheight - ball->radius);

    //check if lost
    if(ball->position.y - ball->radius < bar->position.y + bar->height / 2) {
        *game_state = LOSE_GAME;
        return;
    }
    //check for collisions with the bar
    if(collision(ball, bar->position, bar->width, bar->height)) {
        //TODO: peter change ball direction        
    }
}

void update_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state) {
    //check for collisions with bricks
    for(int i = 0; i < MAX_BRICKS_PER_LEVEL; i++) {
        if(bricks[i]) {
            if(collision(ball, corner_of_brick(i), BRICK_WIDTH, BRICK_HEIGHT)) {
                bricks[i] = 0x0;
                //TODO: peter change ball direction 
            }
        }
    }


}
