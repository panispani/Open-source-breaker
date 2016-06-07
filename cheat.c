#include "includes.h"
#define FLAG_1 0x1
#define FLAG_2 0x2
#define FLAG_3 0x4

static uint32_t cheat;

void reset_cheat() {
    cheat = 0;
}

void set_cheat(int pos) {
    pos--;
    cheat |= (1 << pos);
}

void check_cheat(game_state_t *game_state) {
    if(*game_state == PLAY_GAME) {
        if((cheat & FLAG_1) &&         
           (cheat & FLAG_2) &&         
           (cheat & FLAG_3)) {
            *game_state = WIN_LEVEL;
        }
    }
}
