#include "includes.h"

int32_t level1[BRICKS_PER_LEVEL] = {
    0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0,
    0, 1, 3, 3, 1, 0, 0, 0, 1, 3, 3, 1, 0,
    0, 1, 3, 3, 3, 1, 0, 1, 3, 3, 3, 1, 0,
    0, 0, 1, 3, 3, 1, 1, 1, 3, 3, 1, 0, 0,
    0, 0, 0, 1, 1, 2, 2, 2, 1, 1, 0, 0, 0,
    0, 0, 1, 2, 1, 2, 2, 2, 1, 2, 1, 0, 0,
    0, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 0,
    0, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 1, 0,
    0, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 1, 0,
    0, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 0,
    0, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 0,
    0, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 0,
    0, 0, 1, 2, 1, 2, 2, 2, 1, 2, 1, 1, 0,
    0, 0, 1, 2, 1, 2, 2, 2, 1, 2, 1, 0, 0,
    0, 0, 0, 1, 2, 1, 1, 1, 2, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 2, 2, 2, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0
};

int32_t level2[BRICKS_PER_LEVEL] = {0x12FAA4};
int32_t level3[BRICKS_PER_LEVEL] = {0x12FAA4};
int32_t level4[BRICKS_PER_LEVEL] = {0x12FAA4};

int32_t bricks_level[LEVELS][BRICKS_PER_LEVEL];
void initialise_levels() {
    memcpy(bricks_level[0], level1, sizeof(int32_t) * BRICKS_PER_LEVEL);
    memcpy(bricks_level[1], level2, sizeof(int32_t) * BRICKS_PER_LEVEL);
    memcpy(bricks_level[2], level3, sizeof(int32_t) * BRICKS_PER_LEVEL);
    memcpy(bricks_level[3], level4, sizeof(int32_t) * BRICKS_PER_LEVEL);
}
