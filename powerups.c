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
 * Powerup defaults
 */ 
#define DEF_POWERUP_DY 3
#define DEF_POWERUP_DIAMETER 6
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
 * Powerup type currently in the game
 */ 
static uint8_t current_powerup = NO_POWERUP;

/*
 * current powerup and it's colour
 */ 
ball_t powerup;
uint32_t powerup_colour;

/*
 * Initialise powerup on start of game
 */  
void init_powerup(void) {
    srand(time(NULL));
    reset_powerup();
}

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
        //current_powerup = NO_POWERUP;
    } else if(powerup.position.y + powerup.diameter >= gameheight) {
        current_powerup = NO_POWERUP;
    }
}

/*
 * Randomly assigns a powerup. 10 / 15 powerups are dummy
 * so there is a 1 / 3 chance of getting a powerup
 * Given point is the point of creation
 */ 
void ask_for_powerup(vector2D_t point) {
     if(current_powerup != NO_POWERUP) {
        return;
    }
    powerup_type = rand() % POWERUPS;
    switch(powerup_type) {
        case BIGGER_BAR:
        case SLOWER_BALL:
        case FASTER_BALL:
        case BIGGER_BALL:
        case SMALLER_BALL:
            powerup.position.x = point.x;
            powerup.position.y = point.y;
            powerup.direction.x = 0;
            powerup.direction.y = DEF_POWERUP_DY;
            powerup.diameter = 2 * DEF_POWERUP_DIAMETER;
            break;
    }
}

/*
 * Create a powerup if it was gained before
 */
void give_any_powerup(void) {
    switch(powerup_type) {
        case BIGGER_BAR:
            powerup_colour = palette[RED];
            current_powerup = BIGGER_BAR;
            break;
        case SLOWER_BALL:
            powerup_colour = palette[BLUE];
            current_powerup = SLOWER_BALL;
            break;
        case FASTER_BALL:
            powerup_colour = palette[YELLOW];
            current_powerup = FASTER_BALL;
            break;
        case BIGGER_BALL:
            powerup_colour = palette[GREEN];
            current_powerup = BIGGER_BALL;
            break;
        case SMALLER_BALL:
            powerup_colour = palette[PURPLE];
            current_powerup = SMALLER_BALL;
            break;
    }
    powerup_type = NO_POWERUP;
}

/*
 * Returns true if there is a powerup
 */ 
bool is_powerup(void) {
    return current_powerup != NO_POWERUP;
}

/*
 * Resets powerup for start of a level
 */ 
void reset_powerup(void) {
    current_powerup = NO_POWERUP;
    powerup_type = NO_POWERUP;   
}
