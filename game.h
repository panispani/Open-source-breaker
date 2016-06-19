#ifndef __GAME_H
#define __GAME_H

typedef enum game_state {
    START_GAME, START_MENU, PLAY_GAME, PAUSE_SCREEN,
    LOSE_GAME, GAME_OVER, WIN_LEVEL, WIN_GAME, EXIT_GAME, WAIT_FOR_RESTART
} game_state_t;

typedef enum {
    NONE = 0, VERTICAL = 1, HORIZONTAL = 2
} collision_orientation;

typedef struct {
    double x;
    double y;
} vector2D_t;

typedef struct {
    vector2D_t position;
    vector2D_t direction;
    double diameter;
    bool is_wrecking_ball;
} ball_t;

typedef struct {
    vector2D_t position;
    vector2D_t direction;
    double width;
    double height;
    int8_t level;
    int8_t lives;
} bar_t;

extern int32_t gamewidth;
extern int32_t gameheight;

void init_bar(bar_t *bar);
void reset_bar(bar_t *bar);
void init_ball(ball_t * ball);
void reset_ball(ball_t * ball);
void update_bar(bar_t *bar, int8_t controller_state);
int update_ball(ball_t *ball, bar_t *bar, game_state_t *game_state);
void update_bricks(ball_t *ball, int32_t *bricks, game_state_t *game_state);
void lose_life(bar_t *bar, game_state_t *game_state);
double cram(double x, double left, double right);
vector2D_t corner_of_brick(int n);
collision_orientation collision(ball_t *ball, vector2D_t other, double width, double height);
double min(double a, double b);

#define DEF_BAR_WIDTH 120
#define DEF_BAR_Y (15 * gameheight / 16)
#define DEF_BAR_X (gamewidth / 2 + 20)
#define DEF_BAR_HEIGHT 6
#define DEF_BALL_RADIUS 4
#define DEF_BALL_HEIGHT (2 * gameheight / 3)
#define DEF_BALL_DX 5
#define DEF_BALL_DY 10
#define BAR_MAX_SPEED 19
#define BAR_SPEED_UP 3
#define BAR_BOUNCE 0.5
#define BALL_MAX_SPEED 10
#define BAR_SLOWDOWN 1.25
#define BRICK_X_OFFSET (gamewidth - BRICKS_PER_ROW * BRICK_WIDTH) / 2
#define BRICK_Y_OFFSET (gameheight / 14)
#define LOSE_Y_LIMIT bar->height
#define START_LIVES 3


#endif // __GAME_H
