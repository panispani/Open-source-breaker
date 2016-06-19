#ifndef __CONTROLLER_H
#define __CONTROLLER_H

void initialise_controller();
void reset_controller();
void set_controller(int16_t flag);
int16_t get_controller_state();
void reset_cheat();
void set_cheat();
void check_cheat(game_state_t *game_state);

/* CONTROLLER FLAGS */
#define A_FLAG 0x1
#define D_FLAG 0x2
#define SPACE_FLAG 0x4
#define FLAG_1 0x1
#define FLAG_2 0x2
#define FLAG_3 0x4


#endif
