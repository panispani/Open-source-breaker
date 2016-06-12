#ifndef __POWERUPS_H
#define __POWERUPS_H

extern ball_t powerup;
extern uint8_t powerup_colour;

void update_powerups(bar_t *bar, ball_t *ball);
void ask_for_powerup(vector2D_t point);
void give_any_powerup(void);
bool is_powerup(void);
void reset_powerup(void);

#endif // __POWERUPS_H
