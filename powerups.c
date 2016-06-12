#include "includes.h"
/*
 * Powerups are in fact 5, the other 10 are dummy
 * so that possibility of getting one is not 100%
 */ 
#define POWERUPS 15 
/*
 * Powerup indices
 * rest are dummy
 */ 
#define NO_POWERUP 0
#define BIGGER_BAR 3
#define SLOWER_BALL 6
#define FASTER_BALL 9
#define BIGGER_BALL 12
#define SMALLER_BALL 14
/*
 * Powerup speeds
 */ 
#define POWERUP_DY 3
/*
 * POWERUP GAINS
 */ 
#define BAR_GAIN 5
#define BALL_MAX_SPEED 10
#define BALL_MIN_SPEED 2

/*
 * powerup to be inserted in game
 */ 
static uint8_t powerup_type = NO_POWERUP;

/*
 * Powerup currently in the game
 */ 
static uint8_t current_powerup = NO_POWERUP;

/*
 * Powerups represented by a ball
 */ 
static ball_t powerup;


/*
 * Update player bar, ball according to powerup
 */ 
void gain_powerup(bar_t *bar, ball_t *ball) {
    switch(powerup_type) {
        case BIGGER_BAR:
            bar->width += BAR_GAIN;
            break;
        case SLOWER_BALL:
            ball->direction.x = BALL_MIN_SPEED;
            ball->direction.y = BALL_MIN_SPEED;
            break;
        case FASTER_BALL:
            ball->direction.x = BALL_MAX_SPEED;
            ball->direction.y = BALL_MAX_SPEED;
            break;
        case BIGGER_BALL:
            ball->diameter = 2 * ball->diameter;
            break;
        case SMALLER_BALL:
            ball->diameter = ball->diameter / 2;
            break;
    }
}

/*
 * Move any powerup to the down of the screen
 * Take care of collisions with bar by updating bar
 * Take care of powerups going on bottom and destroy them
 */ 
void update_powerups(bar_t *bar, ball_t *ball) {
    powerup.position.y += powerup.direction.y;
    if(collision(&powerup, bar->position, bar->width, bar->height)) {
        gain_powerup(bar, ball);
        current_powerup = NO_POWERUP;
    } else if(powerup.position.y + powerup.diameter >= gameheight) {
        current_powerup = NO_POWERUP;
    }
}

/*
 * Randomly assigns a powerup. 10 / 15 powerups are dummy
 * so there is a 1 / 3 chance of getting a powerup
 */ 
void ask_for_powerup() {
    powerup_type = rand() % POWERUPS;
}

//TODO:
void give_any_powerup() {
    if(current_powerup != NO_POWERUP) {
        return;
    }
    switch(powerup_type) {
        case BIGGER_BAR:
            break;
        case SLOWER_BALL:
            break;
        case FASTER_BALL:
            break;
        case BIGGER_BALL:
            break;
        case SMALLER_BALL:
            break;
    }
    powerup_type = NO_POWERUP;
}

//TODO draw powerups
