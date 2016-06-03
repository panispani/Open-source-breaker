#include "includes.h"
#define A_FLAG 0x1
#define D_FLAG 0x2
#define SPACE_FLAG 0x4

int main(void) {
    game_state_t game_state = START_GAME;
    initialise_graphics();
    initialise_levels();
    run(game_state);
}

/*
 * Run one game tick, call corresponding function depending on the game_state
 */
void run(game_state_t game_state) {
    bar_t bar;
    ball_t ball;
    int32_t bricks[BRICKS_PER_LEVEL];
    SDL_Event event;
    int32_t controller_state;
    int32_t running = 1;
    while (running) {
        controller_state = 0;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        controller_state |= A_FLAG;
                        break;
                    case SDLK_d:
                        controller_state |= D_FLAG;
                        break;
                    case SDLK_SPACE:
                        controller_state |= SPACE_FLAG; 
                        break;
                    default:
                        break;
                }
            }
        }
        switch (game_state) {
            case START_GAME:
                start_game(&bar, &ball, &game_state, bricks);
                break;
            case START_MENU:
                start_menu(&bar, &ball, &game_state, bricks);
                break;
            case PLAY_GAME:
                play_game(&bar, &ball, &game_state, bricks);
                break;
            case PAUSE_SCREEN:
                pause_screen(&bar, &ball, &game_state, bricks);
                break;
            case LOSE_GAME:
                lose_game(&bar, &ball, &game_state, bricks);
                break;
            case GAME_OVER:
                game_over(&bar, &ball, &game_state, bricks);
                break;
            case WIN_LEVEL:
                win_level(&bar, &ball, &game_state, bricks);
                break;
            case WIN_GAME:
                win_game(&bar, &ball, &game_state, bricks);
                break;
            case EXIT_GAME:
                exit_game();
                break;
            default:
                perror("Error game state not found");
                exit(EXIT_FAILURE);
        }
        refresh_screen();
        SDL_Delay(50);
    }
    exit_game();
}

void start_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    init_bar(bar);
    init_ball(ball);
    load_level(bar, ball, game_state, bricks);
}

void start_menu(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {

}

/*
 * TODO: draw in update function
 */
void play_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    int8_t controller_state = 0;
    check_keys(&controller_state);
    update_bar(bar, controller_state);
    update_ball(ball, bar, game_state);
    update_bricks(ball, bricks, game_state);
    if(*game_state == LOSE_GAME) {
        return;
    }
}

void pause_screen(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {

}

void lose_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    reset_bar(bar);
    reset_ball(ball);
    lose_life(bar, game_state);
    if(*game_state != GAME_OVER) {
        load_level(bar, ball, game_state, bricks);
    }
}

void load_level(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    bricks = bricks_level[bar->level];
    *game_state = PLAY_GAME;
    draw_game(bar, ball, bricks);
}

void game_over(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    draw_gameover_screen();
    restart_on_keypress(game_state);
    game_state = START_GAME;
}

void win_level(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    bar->level = bar->level + 1;
    reset_bar(bar);
    reset_ball(ball);
    load_level(bar, ball, game_state, bricks);
}

void win_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    draw_win_screen();
    restart_on_keypress(game_state);
}

void restart_on_keypress(game_state_t *game_state) {
    *game_state = START_GAME;
}

void exit_game() {
    destroy_graphics();
}
