#include "includes.h"
#define START_LIVES 3
#define DEF_BAR_WIDTH 120
#define DEF_BAR_Y (15 * gameheight / 16)
#define DEF_BAR_X (gamewidth / 2 + 20)
#define DEF_BAR_HEIGHT 6
#define DEF_BALL_RADIUS 4
#define DEF_BALL_HEIGHT (2 * gameheight / 3)
#define DEF_BALL_DX 5
#define DEF_BALL_DY 10
#define BAR_MAX_SPEED 19
#define BAR_SPEED_UP 3
#define BAR_BOUNCE 0.5
#define BALL_MAX_SPEED 10
#define BAR_SLOWDOWN 1.25
#define BRICK_X_OFFSET (gamewidth - BRICKS_PER_ROW * BRICK_WIDTH) / 2
#define BRICK_Y_OFFSET (gameheight / 14)
#define LOSE_Y_LIMIT bar->height

/*
 * Initialise bar at the start of the game
 */ 
void init_bar(bar_t *bar) {
    reset_bar(bar);
    bar->level = 0;
    bar->lives = START_LIVES;
}

/*
 * Update player and gamestate when he loses a life
 */ 
void lose_life(bar_t *bar, game_state_t *game_state) {
    bar->lives--;
    if(bar->lives == 0) {
        *game_state = GAME_OVER;
    } else {
        *game_state = PLAY_GAME;
    }
}

/*
 * Resets bar at the start of a level or when the player lost
 */ 
void reset_bar(bar_t *bar) {
    bar->position.x = DEF_BAR_X;
    bar->position.y = DEF_BAR_Y;
    bar->direction.x = 0;
    bar->width = DEF_BAR_WIDTH;
    bar->height = DEF_BAR_HEIGHT;
}

/*
 * Initialises ball at the start of the game
 */ 
void init_ball(ball_t *ball) {
    reset_ball(ball);
}

/*
 * Resets ball at the start of a level or when the player lost
 */ 
void reset_ball(ball_t * ball) {
    ball->position.x = gamewidth / 2;
    ball->position.y = DEF_BALL_HEIGHT;
    ball->direction.x = DEF_BALL_DX;
    ball->direction.y = DEF_BALL_DY;
    ball->diameter = 2 * DEF_BALL_RADIUS;
}

/*
 * Given left and right limits make sure the given x is 
 * not out of bounds, if this is the case 
 * place it on the nearest bound
 */
double cram(double x, double left, double right) {
    if (left > right) {
        double temp = left;
        right = left;
        left = temp;
    }
    return x < left ? left : (x > right ? right : x);
}

/*
 * Returns minimum of the two input double numbers
 */ 
double min(double a, double b) {
    return a > b ? b : a;
}

/*
 * Check for collisions. Returns:
 * 0: no collision
 * 1: top or bottom collision
 * 2: left or right collision
 */
collision_orientation collision(ball_t *ball, vector2D_t other, double width, double height) {
    if (ball->position.x <= other.x + width &&
        ball->position.y <= other.y + height &&
        ball->position.x + ball->diameter >= other.x &&
        ball->position.y + ball->diameter >= other.y) {
        if (ball->position.y - ball->direction.y > other.y + height ||
            ball->position.y - ball->direction.y + ball->diameter < other.y) {
            return VERTICAL;
        }
        return HORIZONTAL;
    }
    return NONE;
}

vector2D_t corner_of_brick(int n) {
    vector2D_t corner;
    corner.y = BRICK_HEIGHT * (n / BRICKS_PER_ROW) + BRICK_Y_OFFSET;
    corner.x = BRICK_WIDTH * (n % BRICKS_PER_ROW) + BRICK_X_OFFSET;
    return corner;
}

/*
 * Returns non-zero integer in case of collision of ball with bar
 */
int update_ball(ball_t *ball, bar_t *bar, game_state_t *game_state) {
    int collisions = 0;
    ball->position.x = cram(ball->position.x + ball->direction.x, 0, gamewidth  - ball->diameter);
    ball->position.y = cram(ball->position.y + ball->direction.y, 0, gameheight - ball->diameter);
    if (ball->position.x == 0 || ball->position.x + ball->diameter == gamewidth) {
        ball->direction.x *= -1;
    }
    if (ball->position.y == 0 ) {
        ball->direction.y *= -1;
    }

    //check if lost
    if(ball->position.y + ball->diameter == gameheight) {
        *game_state = LOSE_GAME;
        return 0;
    }
    //check for collisions with the bar
    switch(collision(ball, bar->position, bar->width, bar->height)) {
        case VERTICAL:
            ball->direction.y *= -1;
            ball->direction.x = cram(ball->direction.x + bar->direction.x * BAR_BOUNCE,
                    -BALL_MAX_SPEED, BALL_MAX_SPEED);
            collisions++;
            break;
        case HORIZONTAL:
            ball->direction.x *= -1;
            collisions++;
            break;
        default: 
            break;
    }
    return collisions;
}

/*
 * Update the bar position according to the buttons pressed
 */
void update_bar(bar_t *bar, int8_t controller_state) {
    int input = cram((controller_state & 0x2) - (controller_state & 0x1), -1, 1);
    
    bar->direction.x /= BAR_SLOWDOWN;
    bar->direction.x = cram(bar->direction.x + input * BAR_SPEED_UP, -BAR_MAX_SPEED, BAR_MAX_SPEED);
    bar->position.x = cram(bar->position.x + bar->direction.x, 0, gamewidth - bar->width);
}

/*
 * Updates bricks by checking for collisions with the ball
 * The input ball should be already updated
 */
void update_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state) {
    bool win_level = true;
    uint8_t powerup_type = 0;
    for(int i = 0; i < BRICKS_PER_LEVEL; i++) {
        if(bricks[i]) {
            win_level = false;           
            switch(collision(ball, corner_of_brick(i), BRICK_WIDTH, BRICK_HEIGHT)) {
                case VERTICAL:
                    bricks[i] = 0x0;
                    ask_for_powerup(); 
                    ball->direction.y *= -1;
                    break;
                case HORIZONTAL:
                    bricks[i] = 0x0;
                    ask_for_powerup();
                    ball->direction.x *= -1;
                    break;
                default: 
                    break;
            }
        }
    }
    give_any_powerup();
    if (win_level) {
        *game_state = WIN_LEVEL;
    }
}
