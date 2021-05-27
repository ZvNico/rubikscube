#include "enum_types.h"

char *select_color(T_COLOR color) {
    switch (color) {
        case R:
            return "\033[0;31m";
        case B:
            return "\033[0;34m";
        case G:
            return "\033[0;32m";
        case W:
            return "\033[0;37m";
        case Y:
            return "\033[0;33m";
        case O:
            return "\033[38;2;255;165;0m";
        case LG:
            return "\033[0;37m";
    }
}

int side_to_index(T_SIDE side) {
    switch (side) {
        case FRONT:
            return 2;
        case BACK:
            return 5;
        case UP:
            return 1;
        case DOWN:
            return 3;
        case RIGHT:
            return 4;
        case LEFT:
            return 0;
    }
}
