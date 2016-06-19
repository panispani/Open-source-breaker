#include "includes.h"

/*
 * The controller state bits should be set as follows
 * The bottom 3 bits should show the state of the players buttons
 * 1 for pressed, 0 for not pressed. The bottom 3 bits represent
 * the left, right and fire button accordingly
 * (starting from the bottom bit)
 */
static int16_t controller;

/*
 * cheat register that has the current keybinding pressed
 * used for finding possible cheat usage
 */
static uint32_t cheat;

/*
 * Initialise on creation
 */
void initialise_controller() {
    reset_controller();
}

/*
 * Reset controller state for setting
 * new flags - button presses
 */
void reset_controller() {
    controller = 0;
}

/*
 * Set some particualr bits specified by flag in
 * controller
 */
void set_controller(int16_t flag) {
    controller |= flag;
}

/*
 * Returns current controller state
 */
int16_t get_controller_state() {
    return controller;
}


/*
 * Reset cheat at each frame
 */
void reset_cheat() {
    cheat = 0;
}

/*
 * Set a pressed button flag
 */
void set_cheat(int flag) {
    cheat |= flag;
}

/*
 * Check if any of the impelemented cheats is used
 */
void check_cheat(game_state_t *game_state) {
    if(*game_state == PLAY_GAME) {
        if((cheat & FLAG_1) &&
           (cheat & FLAG_2) &&
           (cheat & FLAG_3)) {
            *game_state = WIN_LEVEL;
        }
    }
}

