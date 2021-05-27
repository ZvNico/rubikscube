#ifndef RUBIKSCUBE_ENUM_TYPES_H
#define RUBIKSCUBE_ENUM_TYPES_H

typedef enum {
    FRONT, BACK, UP, DOWN, RIGHT, LEFT
} T_SIDE;

typedef enum {
    R, B, G, W, Y, O, LG
} T_COLOR;

char *select_color(T_COLOR);

int side_to_index(T_SIDE);

#endif //RUBIKSCUBE_ENUM_TYPES_H
