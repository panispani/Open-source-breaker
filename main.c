#include "includes.h"

void run(game_state_t game_state);
void start_game(bar_t *bar, ball_t *ball, game_state_t *game_state);
void start_menu(bar_t *bar, ball_t *ball, game_state_t *game_state);
void play_game(bar_t *bar, ball_t *ball, game_state_t *game_state);
void pause_screen(bar_t *bar, ball_t *ball, game_state_t *game_state);
void lose_game(bar_t *bar, ball_t *ball, game_state_t *game_state);
void game_over(bar_t *bar, ball_t *ball, game_state_t *game_state);
void win_level(bar_t *bar, ball_t *ball, game_state_t *game_state);
void win_game(bar_t *bar, ball_t *ball, game_state_t *game_state);

int main(void) {
    game_state_t game_state = START_GAME;
    run(game_state);    
}


void run(game_state_t game_state) {
    bar_t bar;
    ball_t ball;
    while(1) {
        switch(game_state) {
            case START_GAME:
                start_game(&bar, &ball, &game_state);
                break;
            case START_MENU:
                start_menu(&bar, &ball, &game_state);
                break;
            case PLAY_GAME:
                play_game(&bar, &ball, &game_state);
                break;
            case PAUSE_SCREEN:
                pause_screen(&bar, &ball, &game_state);
                break;
            case LOSE_GAME:
                lose_game(&bar, &ball, &game_state);
                break;
            case GAME_OVER:
                game_over(&bar, &ball, &game_state);
                break;
            case WIN_LEVEL:
                win_level(&bar, &ball, &game_state);
                break;
            case WIN_GAME:
                win_game(&bar, &ball, &game_state);
                break;
            default:
                perror("Error game state not found");
                exit(EXIT_FAILURE);
        }
    }
}

void start_game(bar_t *bar, ball_t *ball, game_state_t *game_state) {
    
}

void start_menu(bar_t *bar, ball_t *ball, game_state_t *game_state) {

}

void play_game(bar_t *bar, ball_t *ball, game_state_t *game_state) {

}

void pause_screen(bar_t *bar, ball_t *ball, game_state_t *game_state) {

}

void lose_game(bar_t *bar, ball_t *ball, game_state_t *game_state) {

}

void game_over(bar_t *bar, ball_t *ball, game_state_t *game_state) {

}

void win_level(bar_t *bar, ball_t *ball, game_state_t *game_state) {

}

void win_game(bar_t *bar, ball_t *ball, game_state_t *game_state) {

}
