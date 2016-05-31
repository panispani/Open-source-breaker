#include "includes.h"

void run(game_state_t game_state);
void start_game();
void start_menu();
void play_game();
void pause_screen();
void lose_game();
void game_over();
void win_level();
void win_game();

int main(void) {
    game_state_t game_state = START_GAME;
    run(game_state);    
}


void run(game_state_t game_state) {
    while(1) {
        switch(game_state) {
            case START_GAME:
                start_game();
                break;
            case START_MENU:
                start_menu();
                break;
            case PLAY_GAME:
                play_game();
                break;
            case PAUSE_SCREEN:
                pause_screen();
                break;
            case LOSE_GAME:
                lose_game();
                break;
            case GAME_OVER:
                game_over();
                break;
            case WIN_LEVEL:
                win_level();
                break;
            case WIN_GAME:
                win_game();
                break;
            default:
                perror("Error game state not found");
                exit(EXIT_FAILURE);
        }
    }
}

void start_game() {

}

void start_menu() {

}

void play_game() {

}

void pause_screen() {

}

void lose_game() {

}

void game_over() {

}

void win_level() {

}

void win_game() {

}
