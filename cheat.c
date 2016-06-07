#include "includes.h"

static uint32_t cheat;

void reset_cheat() {
    cheat = 0;
}

void set_cheat(int pos) {
    pos--;
    cheat |= (1 << pos);
}
void check_cheat() {

}


