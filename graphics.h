#ifndef __GRAPHICS_H
#define __GRAPHICS_H

extern int32_t gamewidth;
extern int32_t gameheight;

void initialise_graphics();
void draw_background();
void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks);
void draw_win_screen();
void draw_gameover_screen();
void destroy_graphics();

#endif //__GRAPHICS_H
