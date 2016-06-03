#ifndef __GRAPHICS_H
#define __GRAPHICS_H

extern int32_t gamewidth;
extern int32_t gameheight;

void initialise_graphics();
void refresh_screen();
void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks);
void draw_background();
void draw_ball(int32_t x, int32_t y, int32_t radius, int32_t colour);
void draw_bar(int32_t x, int32_t y, int32_t width, int32_t height, int32_t colour);
void draw_brick(int32_t x, int32_t y, int32_t width, int32_t height, int32_t colour);
void draw_filled_circle(int32_t x0, int32_t y0, int32_t radius);
void draw_win_screen();
void draw_gameover_screen();
void destroy_graphics();

#endif //__GRAPHICS_H
