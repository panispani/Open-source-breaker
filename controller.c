#include "includes.h"
#define CLEAR_BOTTOM_BITS(n)\
    n &= ~(0x7)

static int16_t controller;

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
 * The controller state bits should be set as follows
 * The bottom 3 bits should show the state of the players buttons
 * 1 for pressed, 0 for not pressed. The bottom 3 bits represent
 * the left, right and fire button accordingly
 * (starting from the bottom bit)
 */ 
void check_keys(int8_t *controller_state) {
    CLEAR_BOTTOM_BITS(*controller_state); 
}
