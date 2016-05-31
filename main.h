#ifndef __MAIN_H
#define __MAIN_H

void run(game_state_t game_state);
void start_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void start_menu(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void play_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void pause_screen(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void lose_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void game_over(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void win_level(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void win_game(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);
void restart_on_keypress(game_state_t *game_state);
void load_level(bar_t *bar, ball_t *ball, game_state_t *game_state, int32_t *bricks);

#endif
