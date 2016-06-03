#include "includes.h"
#define CLEAR_BOTTOM_BITS(n)\
    n &= ~(0x7)


void initialise_controller() {

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
