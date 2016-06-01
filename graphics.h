#ifndef __GRAPHICS_H
#define __GRAPHICS_H

void initialise_graphics();
void draw_background(int32_t color);
void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks);
void draw_win_screen();
void draw_gameover_screen();

#endif //__GRAPHICS_H
