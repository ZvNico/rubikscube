#include "stdlib.h"
#include "rubiks.h"
#include "stdio.h"


Rubiks **create_rubiks() {
    Rubiks **rubiks = (Rubiks **) malloc(6 * sizeof(Rubiks));
    T_SIDE order[] = {LEFT, UP, FRONT, DOWN, RIGHT, BACK};
    int pos;
    for (int i = 0; i < 6; i++) {
        rubiks[i] = (Rubiks *) malloc(sizeof(Rubiks));
        rubiks[i]->Type_face = order[i];
    }
    return rubiks;
}

void init_rubiks(Rubiks **rubiks) {
    T_COLOR side_to_color[] = {O, W, G, Y, R, B};
    T_SIDE actual_side;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                rubiks[i]->Face[j][k] = side_to_color[i];
            }
        }
    }
}

void display_rubiks(Rubiks **rubiks) {
    int i, j, k;
    T_SIDE order[] = {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
    T_SIDE actual_side;
    actual_side = side_to_index(order[0]);
    for (j = 0; j < 3; j++) {
        printf("      ");
        for (k = 0; k < 3; k++) {
            printf("%s", select_color(rubiks[actual_side]->Face[j][k]));
            printf(" ■");
        }
        printf("\n");
    }
    for (j = 0; j < 3; j++) {
        for (i = 1; i < 5; i++) {
            actual_side = side_to_index(order[i]);
            for (k = 0; k < 3; k++) {
                printf("%s", select_color(rubiks[actual_side]->Face[j][k]));
                printf(" ■");
            }
        }
        printf("\n");
    }
    actual_side = side_to_index(order[5]);
    for (j = 0; j < 3; j++) {
        printf("      ");
        for (k = 0; k < 3; k++) {
            printf("%s", select_color(rubiks[actual_side]->Face[j][k]));
            printf(" ■");
        }
        printf("\n");
    }
    printf("\033[0m");
}

void blank_rubiks(Rubiks **rubiks) {
    int i, j, k;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                rubiks[i]->Face[j][k] = LG;
            }
        }
    }
}


void fill_rubiks(Rubiks **rubiks) {
    char *side_initial = "LUFDRB";
    char *color_initial = "RBGWYOE";
    char side;
    char color;
    int x, y, c, s, i, j;
    do {
        printf("Saississez le coté et les coordonnés de la case à modifier\n");
        printf("Coté :\n - (U)P\n - (L)EFT\n - (F)RONT\n - (R)IGHT\n - (B)ACK\n - (D)OWN\n");
        printf("Coordonnées : x ( 0 - 2 ) y ( 0 - 2 ))\nExemple : 'U 2 1'\n");
        scanf("%c %d %d", &side, &x, &y);
    } while ((x < 0 || x > 2 || y < 0 || y > 2) ||
             (side != 'L' & side != 'U' && side != 'F' && side != 'D' && side != 'R' && side != 'B'));
    do {
        printf("Choississez une couleur a affecter à la case %c %d %d\n", side, x, y);
        printf("Couleur :\n\033[0;31m - (R)ED\n\033[0;34m - (B)LUE\n\033[0;32m - (G)REEN\n\033[0;37m - (W)HITE\n\033[0;33m - (Y)ELLOW\n\033[38;2;255;165;0m - (0)RANGE\n\033[0;37m - (E)MPTY ( grey case )\n\033[0m");
        scanf("\n%c", &color);
    } while (color != 'R' && color != 'B' && color != 'G' && color != 'W' && color != 'Y' && color != 'O' &&
             color != 'E');
    for (i = 0; i < 6; i++) {
        if (side == side_initial[i]) {
            s = i;
        }
        if (color == color_initial[i]) {
            c = i;
        }
    }
    if (color == color_initial[6]) {
        c = 76;
    }
    rubiks[s]->Face[y][x] = c;
}

void free_rubiks(Rubiks **rubiks) {
    for (int i = 0; i < 6; i++) {
        free(rubiks[i]);
    }
    free(rubiks);
}

void side_clockwise(Rubiks **rubiks, int type, T_SIDE side) {
    int temp, i, j;
    int iside = side_to_index(side);

    for (i = 0; i < type; i++) {
        // rotation 45° du coté 'side'
        for (j = 0; j < 2; j++) {
            temp = rubiks[iside]->Face[j][2];
            rubiks[iside]->Face[j][2] = rubiks[iside]->Face[0][j];
            rubiks[iside]->Face[0][j] = rubiks[iside]->Face[2 - j][0];
            rubiks[iside]->Face[2 - j][0] = rubiks[iside]->Face[2][2 - j];
            rubiks[iside]->Face[2][2 - j] = temp;
        }
    }
    switch (side) {
        case FRONT:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(RIGHT)]->Face[i][0];
                rubiks[side_to_index(RIGHT)]->Face[i][0] = rubiks[side_to_index(UP)]->Face[2][i];
                rubiks[side_to_index(UP)]->Face[2][i] = rubiks[side_to_index(LEFT)]->Face[2 - i][2];
                rubiks[side_to_index(LEFT)]->Face[2 - i][2] = rubiks[side_to_index(DOWN)]->Face[0][2 - i];
                rubiks[side_to_index(DOWN)]->Face[0][2 - i] = temp;

            }
            break;
        case BACK:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(UP)]->Face[0][i];
                rubiks[side_to_index(UP)]->Face[0][i] = rubiks[side_to_index(LEFT)]->Face[i][0];
                rubiks[side_to_index(LEFT)]->Face[i][0] = rubiks[side_to_index(DOWN)]->Face[2][i];
                rubiks[side_to_index(DOWN)]->Face[2][i] = rubiks[side_to_index(RIGHT)]->Face[2 - i][2];
                rubiks[side_to_index(RIGHT)]->Face[2 - i][2] = temp;
            }
            break;
        case UP:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(RIGHT)]->Face[0][2 - i];
                rubiks[side_to_index(RIGHT)]->Face[0][2 - i] = rubiks[side_to_index(BACK)]->Face[0][2 - i];
                rubiks[side_to_index(BACK)]->Face[0][2 - i] = rubiks[side_to_index(LEFT)]->Face[0][2 - i];
                rubiks[side_to_index(LEFT)]->Face[0][2 - i] = rubiks[side_to_index(FRONT)]->Face[0][2 - i];
                rubiks[side_to_index(FRONT)]->Face[0][2 - i] = temp;
            }
            break;
        case DOWN:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(RIGHT)]->Face[2][i];
                rubiks[side_to_index(RIGHT)]->Face[2][i] = rubiks[side_to_index(FRONT)]->Face[2][i];
                rubiks[side_to_index(FRONT)]->Face[2][i] = rubiks[side_to_index(LEFT)]->Face[2][i];
                rubiks[side_to_index(LEFT)]->Face[2][i] = rubiks[side_to_index(BACK)]->Face[2][i];
                rubiks[side_to_index(BACK)]->Face[2][i] = temp;
            }
            break;
        case RIGHT:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(BACK)]->Face[i][0];
                rubiks[side_to_index(BACK)]->Face[i][0] = rubiks[side_to_index(UP)]->Face[2 - i][2];
                rubiks[side_to_index(UP)]->Face[2 - i][2] = rubiks[side_to_index(FRONT)]->Face[i][2];
                rubiks[side_to_index(FRONT)]->Face[i][2] = rubiks[side_to_index(DOWN)]->Face[2 - i][2];
                rubiks[side_to_index(DOWN)]->Face[2 - i][2] = temp;
            }
            break;
        case LEFT:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(FRONT)]->Face[i][0];
                rubiks[side_to_index(FRONT)]->Face[i][0] = rubiks[side_to_index(UP)]->Face[i][0];
                rubiks[side_to_index(UP)]->Face[i][0] = rubiks[side_to_index(BACK)]->Face[2 - i][2];
                rubiks[side_to_index(BACK)]->Face[2 - i][2] = rubiks[side_to_index(DOWN)]->Face[i][0];
                rubiks[side_to_index(DOWN)]->Face[i][0] = temp;
            }
            break;
    }

}

void side_antilockwise(Rubiks **rubiks, int type, T_SIDE side) {
    int temp, i, j;
    int iside = side_to_index(side);

    for (i = 0; i < type; i++) {
        // rotation - 45° du coté 'side'
        for (j = 0; j < 3; j++) {
            temp = rubiks[iside]->Face[0][j];
            rubiks[iside]->Face[0][j] = rubiks[iside]->Face[j][2];
            rubiks[iside]->Face[j][2] = rubiks[iside]->Face[2][2 - j];
            rubiks[iside]->Face[2][2 - j] = rubiks[iside]->Face[2 - j][0];
            rubiks[iside]->Face[2 - j][0] = temp;
        }
    }
    switch (side) {
        case FRONT:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(UP)]->Face[2][i];
                rubiks[side_to_index(UP)]->Face[2][i] = rubiks[side_to_index(RIGHT)]->Face[i][0];
                rubiks[side_to_index(RIGHT)]->Face[i][0] = rubiks[side_to_index(DOWN)]->Face[0][2 - i];
                rubiks[side_to_index(DOWN)]->Face[0][2 - i] = rubiks[side_to_index(LEFT)]->Face[2 - i][2];
                rubiks[side_to_index(LEFT)]->Face[2 - i][2] = temp;
            }
            break;
        case BACK:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(UP)]->Face[0][i];
                rubiks[side_to_index(UP)]->Face[0][i] = rubiks[side_to_index(LEFT)]->Face[i][0];
                rubiks[side_to_index(LEFT)]->Face[i][0] = rubiks[side_to_index(DOWN)]->Face[2][i];
                rubiks[side_to_index(DOWN)]->Face[2][i] = rubiks[side_to_index(RIGHT)]->Face[2 - i][2];
                rubiks[side_to_index(RIGHT)]->Face[2 - i][2] = temp;
            }
            break;
        case UP:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(BACK)]->Face[0][2 - i];
                rubiks[side_to_index(BACK)]->Face[0][2 - i] = rubiks[side_to_index(RIGHT)]->Face[0][2 - i];
                rubiks[side_to_index(RIGHT)]->Face[0][2 - i] = rubiks[side_to_index(FRONT)]->Face[0][2 - i];
                rubiks[side_to_index(FRONT)]->Face[0][2 - i] = rubiks[side_to_index(LEFT)]->Face[0][2 - i];
                rubiks[side_to_index(LEFT)]->Face[0][2 - i] = temp;
            }
            break;
        case DOWN:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(FRONT)]->Face[2][i];
                rubiks[side_to_index(FRONT)]->Face[2][i] = rubiks[side_to_index(RIGHT)]->Face[2][i];
                rubiks[side_to_index(RIGHT)]->Face[2][i] = rubiks[side_to_index(BACK)]->Face[2][i];
                rubiks[side_to_index(BACK)]->Face[2][i] = rubiks[side_to_index(LEFT)]->Face[2][i];
                rubiks[side_to_index(LEFT)]->Face[2][i] = temp;
            }
            break;
        case RIGHT:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(UP)]->Face[2 - i][2];
                rubiks[side_to_index(UP)]->Face[2 - i][2] = rubiks[side_to_index(BACK)]->Face[i][0];
                rubiks[side_to_index(BACK)]->Face[i][0] = rubiks[side_to_index(DOWN)]->Face[2 - i][2];
                rubiks[side_to_index(DOWN)]->Face[2 - i][2] = rubiks[side_to_index(FRONT)]->Face[i][2];
                rubiks[side_to_index(FRONT)]->Face[i][2] = temp;
            }
            break;
        case LEFT:
            for (i = 0; i < 3; i++) {
                temp = rubiks[side_to_index(UP)]->Face[i][0];
                rubiks[side_to_index(UP)]->Face[i][0] = rubiks[side_to_index(FRONT)]->Face[i][0];
                rubiks[side_to_index(FRONT)]->Face[i][0] = rubiks[side_to_index(DOWN)]->Face[i][0];
                rubiks[side_to_index(DOWN)]->Face[i][0] = rubiks[side_to_index(BACK)]->Face[2 - i][2];
                rubiks[side_to_index(BACK)]->Face[2 - i][2] = temp;
            }
            break;
    }
}

void horizontal_rotation(Rubiks **rubiks) {
    Rubiks *ptr;

    ptr = rubiks[side_to_index(FRONT)];
    rubiks[side_to_index(BACK)] = rubiks[side_to_index(FRONT)];
    rubiks[side_to_index(FRONT)] = ptr;

    ptr = rubiks[side_to_index(LEFT)];
    rubiks[side_to_index(RIGHT)] = rubiks[side_to_index(LEFT)];
    rubiks[side_to_index(LEFT)] = ptr;

    // rotation 90° du coté 'side'
    int temp, i, j, k;
    T_SIDE sides[] = {UP, DOWN};
    for (k = 0; k < 2; k++) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                temp = (*rubiks[side_to_index(sides[k])]).Face[j][2];
                rubiks[side_to_index(sides[k])]->Face[j][2] = rubiks[side_to_index(sides[k])]->Face[0][j];
                rubiks[side_to_index(sides[k])]->Face[0][j] = rubiks[side_to_index(sides[k])]->Face[2 - j][0];
                rubiks[side_to_index(sides[k])]->Face[2 - j][0] = rubiks[side_to_index(sides[k])]->Face[2][2 - j];
                rubiks[side_to_index(sides[k])]->Face[2][2 - j] = temp;
            }
        }
    }
}

void vertical_rotation(Rubiks **rubiks) {
    Rubiks *ptr;

    ptr = rubiks[side_to_index(FRONT)];
    rubiks[side_to_index(BACK)] = rubiks[side_to_index(FRONT)];
    rubiks[side_to_index(FRONT)] = ptr;

    ptr = rubiks[side_to_index(UP)];
    rubiks[side_to_index(DOWN)] = rubiks[side_to_index(UP)];
    rubiks[side_to_index(UP)] = ptr;
}

void move_rubiks(Rubiks *rubiks) {
    int input, type, s, i;
    char side;
    char *side_initial = "FBUDRL";
    do {
        printf("Choisissez une action :\n 1 - Rotation sens des aiguilles\n 2 - Rotation sens inverse des aiguilles\n 3 - Rotation horizontale\n 4 - Rotation verticale\n");
        scanf("%d", &input);
    } while (input != 1 && input != 2 && input != 3 && input != 4);
    if (input == 1 || input == 2) {
        do {
            printf(" 1 - Quart de tour\n 2 - Demi tour\n");
            scanf("%d", &type);
        } while (type != 1 && type != 2);
        do {
            printf("Coté :\n - (U)P\n - (L)EFT\n - (F)RONT\n - (R)IGHT\n - (B)ACK\n - (D)OWN\n");
            scanf("\n%c", &side);
        } while (side != 'U' && side != 'L' && side != 'F' && side != 'R' && side != 'B' && side != 'D');
        for (i = 0; i < 6; i++) {
            if (side == side_initial[i]) {
                s = i;
                break;
            }
        }
        if (input == 1) {
            side_clockwise(rubiks, type, s);
        } else {
            side_antilockwise(rubiks, type, s);
        }
    } else if (input == 3) {
        horizontal_rotation(&rubiks);
    } else {
        vertical_rotation(&rubiks);
    }
}

void perfect_cross(Rubiks *rubiks) {

}