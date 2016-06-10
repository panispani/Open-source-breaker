#include "includes.h"
#define RED_FLAG 0xFF0000
#define GREEN_FLAG 0x00FF00
#define BLUE_FLAG 0x0000FF
#define RED_POS 16
#define GREEN_POS 8
#define BLUE_POS 0

// 'global' variables to store screen info
int32_t screenwidth;
int32_t screenheight;
int32_t gamewidth;
int32_t gameheight;
SDL_Window *window;
SDL_DisplayMode DM;
SDL_Renderer *renderer;
TTF_Font *font;
TTF_Font *font_small;
/*
 * Initialise screenwidth, height and open frame buffer device
 */
void initialise_graphics() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { //audio for later
        fprintf(stderr, "error in initialisation of sdl");
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        fprintf(stderr, "error in initialisation of sdl_ttf");
        exit(EXIT_FAILURE);
    }
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        free(window);
        fprintf(stderr, "Error in creating renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    font = TTF_OpenFont("display.ttf", 200);
    if (!font) {
        fprintf(stderr, "Error loading the font");
        exit(EXIT_FAILURE);
    }
    font_small = TTF_OpenFont("display.ttf", 100);
    if (!font_small) {
        fprintf(stderr, "Error loading the font");
        exit(EXIT_FAILURE);
    }
    // SDL_SetRenderDrawColor(renderer, 0x00, 0x0, 0x00, 1);
    // SDL_RenderFillRect(renderer, NULL);
    screenwidth = gamewidth = DM.w;
    screenheight = gameheight = DM.h;
}

void draw_background() {
    SDL_SetRenderDrawColor(renderer, BACK_R, BACK_G, BACK_B, BACK_A);
    SDL_RenderFillRect(renderer, NULL);
}

void refresh_screen(bar_t *bar, ball_t *ball, int32_t *bricks) {
    SDL_RenderClear(renderer);
    draw_background();
    // background
    draw_game(bar, ball, bricks);
    SDL_RenderPresent(renderer);
}

/*
 * Free any memory assocaited for graphics
 */
void destroy_graphics() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*
 * Get red green blue values to represent input colour
 */
void get_rgba(uint32_t colour, uint8_t *red, uint8_t *green, uint8_t *blue, uint8_t* alpha) {
    *red = (colour & RED_FLAG) >> RED_POS;
    *green = (colour & GREEN_FLAG) >> GREEN_POS;
    *blue = (colour & BLUE_FLAG) >> BLUE_POS;
    *alpha = SDL_ALPHA_OPAQUE;
}

/*
 * Draw player bar
 */
void draw_bar(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t colour) {
    SDL_Rect bar;
    bar.x = x;
    bar.y = y;
    bar.w = width;
    bar.h = height;
    uint8_t red, green, blue, alpha;
    get_rgba(colour, &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderDrawRect(renderer, &bar);
}

/*
 * Draw a brick at start or when destroyed
 */
void draw_brick(int32_t x, int32_t y, int32_t width, int32_t height, int32_t colour) {
    SDL_Rect brick;
    brick.x = x;
    brick.y = y;
    brick.w = width;
    brick.h = height;
    uint8_t red, green, blue, alpha;
    get_rgba(colour, &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderFillRect(renderer, &brick);
}

/*
 * Draw the ball to the background color or to its new position
 */
void draw_ball(int32_t x, int32_t y, int32_t radius, int32_t colour) {
    uint8_t red, green, blue, alpha;
    get_rgba(colour, &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    draw_filled_circle(x + radius, y + radius, radius);
}

/*
 * Draw the initial game, used ONLY there
 */
void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks) {
    draw_bar(bar->position.x, bar->position.y, bar->width, bar->height, BAR_COLOUR);
    for(int32_t i = 0; i < BRICKS_PER_LEVEL; i++) {
        if (bricks[i]) {
            vector2D_t corner = corner_of_brick(i);
            draw_brick(corner.x, corner.y, BRICK_WIDTH, BRICK_HEIGHT,
                palette[bricks[i]]);
        }
    }
    draw_ball(ball->position.x, ball->position.y, ball->diameter / 2, BALL_COLOUR);
}

/*
 * Draw a filled circle with center (x0, y0) and the given radius
 */
void draw_filled_circle(int32_t x0, int32_t y0, int32_t radius) {
    int32_t x = 0, y = radius;
    int32_t error = 1 - radius;
    do {
        if (error < 0) {
            x++;
            y++;
            error = error + 2 * x + 3;
        } else {
            x++;
            y--;
            error = error + 2 * x - 2 * y + 5;
        }
        for(int32_t y = -radius; y <= radius; y++) {
           for(int32_t x = -radius; x <= radius; x++) {
                if(x * x+ y * y <= radius * radius) {
                    SDL_RenderDrawPoint(renderer,x0 + x,y0 + y);
                }
            }
        }
    } while (x < y);
}

/*
 * Draw screen when winning the game
 */
void draw_win_screen() {
    render_text("YOU WIN!");
    SDL_Delay(2000);
}

/*
 * Draw the game over screen
 */
void draw_gameover_screen() {
    render_text("GAME OVER");
    SDL_Delay(2000);
}

/*
 * Color pixel (x, y) with color c
 */
void draw_pixel(SDL_Renderer* renderer, int32_t x, int32_t y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

/*
 * Draw a line from (x0, y0) to (y0, y1)
 */
void draw_line(SDL_Renderer* renderer, int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
    int32_t out = SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
    if (out) {
        fprintf(stderr, "Error when drawing the line\n");
        destroy_graphics();
        exit(EXIT_FAILURE);
    }
}

/*
 * Draw a filled circle using the
 * Midpoint circle algorithm
 */
void draw_circle(int32_t x0, int32_t y0, int32_t radius) {
     int32_t x = 0, y = radius;
     int32_t dp = 1 - radius;
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

void render_text(const char *text) {
    SDL_Texture *texture;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, white);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
    SDL_Rect main_title;
    SDL_QueryTexture(texture, NULL, NULL, &main_title.w, &main_title.h);
    main_title.x = (screenwidth - main_title.w) / 2;
    main_title.y = (screenheight - main_title.h) / 2;
    SDL_RenderClear(renderer);
    draw_background();
    SDL_RenderCopy(renderer, texture, NULL, &main_title);
    SDL_RenderPresent(renderer);
}

void render_text_two_lines(const char *text1, const char *text2) {
    SDL_Texture *texture;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text1, white);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
    SDL_Rect main_title;
    SDL_QueryTexture(texture, NULL, NULL, &main_title.w, &main_title.h);
    main_title.x = (screenwidth - main_title.w) / 2;
    main_title.y = screenheight / 2 - main_title.h;
    text_surface = TTF_RenderText_Solid(font_small, text2, white);
    SDL_Texture *texture2;
    texture2 = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
    SDL_Rect sub_title;
    SDL_QueryTexture(texture2, NULL, NULL, &sub_title.w, &sub_title.h);
    sub_title.x = (screenwidth - sub_title.w) / 2;
    sub_title.y = screenheight / 2;
    SDL_RenderClear(renderer);
    draw_background();
    SDL_RenderCopy(renderer, texture, NULL, &main_title);
    SDL_RenderCopy(renderer, texture2, NULL, &sub_title);
    SDL_RenderPresent(renderer);    
}
