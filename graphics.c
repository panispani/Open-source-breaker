#include "includes.h"
#define OFFSET(x, y)\
    x * screenwidth + y

int32_t *framebuffer;
int32_t screenwidth;
int32_t screenheight;
int32_t gamewidth;
int32_t gameheight;
struct fb_var_screeninfo vinfo;

void initialise_graphics() {
    int buffer_status = open("/dev/fb0", O_RDWR);
    if(!buffer_status) {
        fprintf(stderr, "Error cannot open framebuffer");
        exit(EXIT_FAILURE);
    }
    if(ioctl(buffer_status, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("Error reading screen information");
    }
    screenwidth = vinfo.xres;
    screenheight = vinfo.yres;
    gamewidth = screenwidth / 2;
    gameheight = screenheight;
}

void draw_pixel(int x, int y, int32_t colour) {
    *(framebuffer + OFFSET(x, y)) = colour;
}

void draw_background(int32_t color) {

}

void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks) {

}

void draw_win_screen() {

}

void draw_gameover_screen() {

}


