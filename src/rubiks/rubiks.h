#ifndef RUBIKSCUBE_RUBIKS_H
#define RUBIKSCUBE_RUBIKS_H

#include "../enum_types/enum_types.h"

typedef struct {
    T_SIDE Type_face;
    T_COLOR Face[3][3];
} Rubiks;

Rubiks **create_rubiks();

void init_rubiks(Rubiks **);

void display_rubiks(Rubiks **);

void blank_rubiks(Rubiks **);

void fill_rubiks(Rubiks **);

void scramble_rubiks(Rubiks **);

void free_rubiks(Rubiks **);

void side_clockwise(Rubiks **, int, T_SIDE);

void side_anticlockwise(Rubiks **, int, T_SIDE);

void horizontal_rotation(Rubiks **);

void vertical_rotation(Rubiks **);

void move_rubiks(Rubiks*);

void perfect_cross(Rubiks*);
#endif //RUBIKSCUBE_RUBIKS_H
