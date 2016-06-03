#ifndef __GRAPHICS_H
#define __GRAPHICS_H

extern int32_t gamewidth;
extern int32_t gameheight;

void initialise_graphics();
void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks);
void draw_background();
void draw_ball(int x, int y, int radius, int32_t colour);
void draw_bar(int x, int y, int width, int height, int32_t colour);
void draw_brick(int x, int y, int width, int height, int32_t colour);
void draw_filled_circle(int x0, int y0, int radius);
void draw_win_screen();
void draw_gameover_screen();
void destroy_graphics();

#endif //__GRAPHICS_H
