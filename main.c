#include "includes.h"
#define MAX_BRICKS_PER_LEVEL 150

int main(void) {
    game_state_t game_state = START_GAME;
    run(game_state);    
}

/*
 * Run one game tick, call corresponding function depending on the game_state
 */ 
void run(game_state_t game_state) {
    bar_t bar;
    ball_t ball;
    int32_t bricks[MAX_BRICKS_PER_LEVEL];
    while(1) {
        switch(game_state) {
            case START_GAME:
                start_game(&bar, &ball, &game_state, bricks);
                break;
            case START_MENU:
                start_menu(&bar, &ball, &game_state,bricks);
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
            default:
                perror("Error game state not found");
                exit(EXIT_FAILURE);
        }
    }
}

void start_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    init_bar(bar);
    init_ball(ball);
    load_level(bar, ball, game_state, bricks);
}

void start_menu(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {

}

void play_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    int8_t controller_state = 0;
    check_keys(&controller_state);
    update_bar(bar, controller_state);
    update_ball_bricks(ball, bricks, game_state);
    if(*game_state == LOSE_GAME) {
        return;
    }
    draw_background(background_palette[3]);
    draw_game(bar, ball, bricks);
}

void pause_screen(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {

}

void lose_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    reset_bar(bar);
    reset_ball(ball);
    load_level(bar, ball, game_state, bricks);
}

void load_level(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    bricks = bricks_level[bar->level];
    *game_state = PLAY_GAME;     
    draw_background(rand() % sizeof(background_palette));
    draw_game(bar, ball, bricks);
}

void game_over(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks) {
    draw_gameover_screen();
    restart_on_keypress(game_state);
    int8_t controller_state = 0;
    while(!controller_state) {
        check_keys(&controller_state);    
    }
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
    int8_t controller_state = 0;
    while(!controller_state) {
        check_keys(&controller_state);    
    }
    *game_state = START_GAME;
}
