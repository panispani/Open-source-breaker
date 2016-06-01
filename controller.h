#ifndef __CONTROLLER_H
#define __CONTROLLER_H

/*
 * The controller state bits should be set as follows
 * The bottom 3 bits should show the state of the players buttons
 * 1 for pressed, 0 for not pressed. The bottom 3 bits represent
 * the left, right and fire button accordingly
 * (starting from the bottom bit)
 */ 
void check_keys(int8_t *controller_state);

#endif
