#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "includes.h"

// 'global' variables to store screen info
int screenwidth;
int screenheight;
int gamewidth;
int gameheight;
SDL_Window *window;
SDL_DisplayMode DM;
SDL_Renderer *ball_renderer;
SDL_Renderer *bar_renderer;
SDL_Renderer *background_renderer;
SDL_Renderer *brick_renderer;

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
    ball_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    bar_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    background_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    brick_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //TODO; is this safe?
    if(ball_renderer == NULL || bar_renderer == NULL || background_renderer == NULL || brick_renderer == NULL) {
        free(window);
        free(ball_renderer);
        free(bar_renderer);
        free(background_renderer);
        free(brick_renderer);
        fprintf(stderr, "Error in creating renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetRenderDrawColor(ball_renderer, BALL_R, BALL_G, BALL_B, BALL_A);
    SDL_SetRenderDrawColor(bar_renderer, BAR_R, BAR_G, BAR_B, BAR_A);
    SDL_SetRenderDrawColor(background_renderer, BACK_R, BACK_G, BACK_B, BACK_A);
    screenwidth = gamewidth = DM.w;
    screenheight = gameheight = DM.h;
}

/*
 * Free any memory assocaited for graphics
 */
void destroy_graphics() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(ball_renderer);
    SDL_DestroyRenderer(bar_renderer);
    SDL_DestroyRenderer(background_renderer);
    SDL_DestroyRenderer(brick_renderer);
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
 * Draw a line from (x0, y0) to (y0, y1)
 */
void draw_line(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    int out = SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
    if (out) {
        fprintf(stderr, "Error when drawing the line\n");
        destroy_graphics();
        exit(EXIT_FAILURE);
    }
}
/*
 * x and y are the center coordinates of the rectangle
 */
void draw_rect(int center_x, int center_y, int width, int height, uint32_t colour) {
    SDL_Rect rectangle;
    rectangle.x = center_x;
    rectangle.y = center_y;
    rectangle.w = width;
    rectangle.h = height;
    int red = ((EIGHTBIT_MASK << 16) && colour) >> 16;
    int green = ((EIGHTBIT_MASK << 8) && colour) >> 8;
    int blue = EIGHTBIT_MASK && colour;
    SDL_SetRenderDrawColor(background_renderer, red, green, blue, 0);
    int res = SDL_RenderFillRect(background_renderer, &rectangle);
    if (res) {
        perror("Error when drawing the rectangle\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * Draw a filled circle using the
 * Midpoint circle algorithm
 */

 void draw_circle(SDL_Renderer* renderer, int x0, int y0, int radius, int colour) {
     int red = ((EIGHTBIT_MASK << 16) && colour) >> 16;
     int green = ((EIGHTBIT_MASK << 8) && colour) >> 8;
     int blue = EIGHTBIT_MASK && colour;
     SDL_SetRenderDrawColor(renderer, red, green, blue, 0);
     int x = 0, y = radius;
     int dp = 1 - radius;
     do {
         if (dp < 0) {
             dp = dp + 2 * (++x) + 3;
         } else {
             dp = dp + 2 * (++x) - 2 * (--y) + 5;
         }
         draw_pixel(renderer, x0 + x, y0 + y);
         draw_pixel(renderer, x0 - x, y0 + y);
         draw_pixel(renderer, x0 + x, y0 - y);
         draw_pixel(renderer, x0 - x, y0 - y);
         draw_pixel(renderer, x0 + y, y0 + x);
         draw_pixel(renderer, x0 - y, y0 + x);
         draw_pixel(renderer, x0 + y, y0 - x);
         draw_pixel(renderer, x0 - y, y0 - x);
     } while (x < y);
 }

 //NEED TO FIX COLOURS
void draw_filled_circle(SDL_Renderer* renderer, int x0, int y0, int radius, int colour) {
     int red = ((EIGHTBIT_MASK << 16) && colour) >> 16;
     int green = ((EIGHTBIT_MASK << 8) && colour) >> 8;
     int blue = EIGHTBIT_MASK && colour;
     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
     int x = 0, y = radius;
     int dp = 1 - radius;
     do {
         if (dp < 0) {
             dp = dp + 2 * (++x) + 3;
         } else {
             dp = dp + 2 * (++x) - 2 * (--y) + 5;
         }
         for(int y=-radius; y<=radius; y++) {
             for(int x=-radius; x<=radius; x++) {
                 if(x*x+y*y <= radius*radius) {
                     draw_pixel(renderer, x0+x, y0+y);
                 }
             }
         }

     } while (x < y);
}

//NEED TO FIX COLOURS
void draw_circle(SDL_Renderer* renderer, float time) {
    for(int i = 0; i<=360; i++) {
        draw_pixel(SDL_Renderer* renderer, int x, int y)
        draw_pixel(renderer, (200 + (100*cos(i))), (100 + (100*sin(i))));
    }
    for(int j = 0; j<=100; j++) {
        draw_pixel(renderer, (200 + (j*cos(time))), (100 + (j*sin(time))));
    }
    Sleep(1000);
}

void draw_background() {
    SDL_RenderDrawRect(background_renderer, NULL);
}

void draw_bar(int center_x, int center_y, int width, int height) {
    SDL_Rect bar;
    bar.x = center_x - width / 2;
    bar.y = center_y - height / 2;
    bar.w = width;
    bar.h = height;
    SDL_RenderDrawRect(bar_renderer, &bar);
}

void draw_brick(int center_x, int center_y, int width, int height, int32_t colour) {
    SDL_Rect brick;
    brick.x = center_x - width / 2;
    brick.y = center_y - height / 2;
    brick.w = width;
    brick.h = height;
    //TODO set renderer COLOUR
    SDL_RenderDrawRect(brick_renderer, &brick);    
}


//TODO REMOVE ALLLLLLL CENTERS
void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks) {
    draw_bar(bar->position.x, bar->position.y, bar->width, bar->height); 
    for(int i = 0; i < MAX_BRICKS_PER_LEVEL; i++) {
        vector2D_t center = center_of_brick(i);
        draw_brick(center.x, center.y, BRICK_WIDTH, BRICK_HEIGHT, bricks_level[bar->level][i]);
    }
    draw_cirle(ball->position.x, ball->position.y, ball->radius); // ball
}

