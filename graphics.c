#include "includes.h"
#include <SDL2/SDL.h>

// 'global' variables to store screen info
char *fbp = NULL;
int screenwidth;
int screenheight;
int gamewidth;
int gameheight;
SDL_Window *window;
SDL_DisplayMode DM;

/*
 * Initialise screenwidth, height and open frame buffer device
 */ 
void initialise_graphics() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GetCurrentDisplayMode(0, &DM);
    window = SDL_CreateWindow(
            "OPENSOURCE BREAKER",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            DM.w,
            DM.h,
            SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS
    );
    if(window == NULL) {
        fprintf(stderr, "Could not create window %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } 

    /*screenwidth = vinfo.xres;  
    screenheight = vinfo.yres;     
    gamewidth = screenwidth / 2;
    gameheight = screenheight;
    */
}

/*
 * Free any memory allocated for graphics
 */ 
void destroy_graphics() {
    SDL_DestroyWindow(window);
    SDL_Quit(); 
}

/*
 * Draw screen when winning the game
 */
void draw_win_screen() {

}

/*
 * Draw the game over screen
 */
void draw_gameover_screen() {

}


/*
 * Color pixel (x, y) with color c
 */

void draw_pixel(SDL_Renderer* renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

/*
 * x and y are the center coordinates of the rectangle
 */
void draw_rect(int center_x, int center_y, int width, int height, int32_t colour) {
    int x = center_x - width / 2;
    int y = center_y - height / 2;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            //put_pixel(i + x, y + j, colour);
        }
    }
}

/*
 * Draw a filled circle using the
 * Midpoint circle algorithm
 */

void draw_cirle(int x0, int y0, int radius) {
    int32_t colour = BALL_COLOUR;
    int x = 0, y = radius;
    int error = 1 - radius;
    while(x < y) {
        if(error < 0) {
            x++;
            error += 2 * x + 3;
        } else {
            x++;
            y--;
            error += 2 * x - 2 * y + 5;
        }
        //45 degree quadrants
        //put_pixel(x0 + x, y0 + y, colour);
        //put_pixel(x0 - x, y0 + y, colour);
        //put_pixel(x0 + x, y0 - y, colour);
        //put_pixel(x0 - x, y0 - y, colour);
        //put_pixel(x0 + y, y0 + x, colour);
        //put_pixel(x0 - y, y0 + x, colour);
        //put_pixel(x0 + y, y0 - x, colour);
        //put_pixel(x0 - y, y0 - x, colour);
    }
}


void draw_background(int32_t colour) {
    draw_rect(screenwidth / 2, screenheight / 2, screenwidth, screenheight, colour);
}

void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks) {
    draw_rect(bar->position.x, bar->position.y, bar->width, bar->height, BAR_COLOUR); //bar
    for(int i = 0; i < MAX_BRICKS_PER_LEVEL; i++) {
        vector2D_t center = center_of_brick(i);
        draw_rect(center.x, center.y, BRICK_WIDTH, BRICK_HEIGHT, bricks_level[bar->level][i]);
    }
    draw_cirle(ball->position.x, ball->position.y, ball->radius); // ball
}

