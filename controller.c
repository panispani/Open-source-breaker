#include "includes.h"
#define MAX_BUTTONS 10
#define CLEAR_BOTTOM_BITS(n)\
    n &= ~(0x7)
#define IS_LEFT(c)\
    c == 'a' || c == 'A'
#define IS_RIGHT(c)\
    c == 'd' || c == 'D'
#define IS_FIRE(c)\
    c == ' '

int keyboard_buffer;
char buffer[MAX_BUTTONS];

void initialise_controller() {
    if ((keyboard_buffer = open("/dev/port", O_RDWR)) < 0) {
        fprintf(stderr, "Cannot open /dev/port");
        exit(EXIT_FAILURE);
    }
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
    int bytes = read(keyboard_buffer, buffer, MAX_BUTTONS);
    if(bytes == -1) {
        fprintf(stderr, "Error reading from keyboard buffer");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < bytes; i++) {
        if(IS_LEFT(buffer[i])) {
            *controller_state |= 0x1;
        } else if (IS_RIGHT(buffer[i])) {
            *controller_state |= 0x2;
        } else if (IS_FIRE(buffer[i])) {
            *controller_state |= 0x4;
        }
    }
}
