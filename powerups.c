#include "includes.h"
/*
 * Powerups are in fact 4, the other 11 are dummy
 * so that possibility of getting one is not 100%
 */ 
#define POWERUPS 15 

static uint8_t powerup_type = 0;

/*
 * Move any powerups to the down of the screen
 * Take care of collisions with bar by updating bar
 * Take care of powerups going on bottom and destroy them
 */ 
void update_powerups(bar_t *bar) {

}

void ask_for_powerup() {
    powerup_type = rand() % POWERUPS;
}

void give_any_powerup() {

}


