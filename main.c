#include "includes.h"

int main(void) {
    initialise_graphics();
    initialise_music();
    initialise_levels();
    initialise_controller();
    run();
}

/*
 * Run one game tick, call corresponding function depending on the game_state
 */
void run() {
    game_state_t game_state = START_GAME;
    bar_t bar;
    ball_t ball;
    int32_t bricks[BRICKS_PER_LEVEL];
    SDL_Event event;
    int32_t running = 1;
    while (running) {
        reset_controller();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        set_controller(A_FLAG);
                        break;
                    case SDLK_d:
                        set_controller(D_FLAG);
                        break;
                    case SDLK_SPACE:
                        set_controller(SPACE_FLAG);
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
        refresh_screen(&bar, &ball, bricks);
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
 * TODO: draw here
 */
void play_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    int collision = 0;
    update_bar(bar, get_controller_state());
    collision += update_ball(ball, bar, game_state);
    collision += update_bricks(ball, bricks, game_state);
    if(collision) {
        play_collision_sound();
    }
}

void pause_screen(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {

}

void lose_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    draw_ball(ball->position.x, ball->position.y,
            ball->diameter / 2, BACK_COLOUR); //on background colour
    draw_bar(bar->position.x, bar->position.y,
            bar->width, bar->height, BACK_COLOUR); //background colour
    reset_bar(bar);
    reset_ball(ball);
    lose_life(bar, game_state);
    if(*game_state != GAME_OVER) {
        load_level(bar, ball, game_state, bricks);
    }
}

void load_level(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    memcpy(bricks, bricks_level[bar->level], sizeof(int32_t) * BRICKS_PER_LEVEL);
    *game_state = PLAY_GAME;
    draw_game(bar, ball, bricks);
}

void game_over(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    draw_gameover_screen();
    restart_on_keypress(game_state);
    *game_state = START_GAME;
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

//TODO: CORRECT THIS
void restart_on_keypress(game_state_t *game_state) {
    *game_state = START_GAME;
}

void exit_game() {
    destroy_graphics();
}
