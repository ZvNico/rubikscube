#include <stdio.h>
#include "src/enum_types/enum_types.h"
#include "src/rubiks/rubiks.h"

int main() {
    Rubiks **rubiks = create_rubiks();
    init_rubiks(rubiks);
    display_rubiks(rubiks);
    while (1) {
        move_rubiks(rubiks);
        display_rubiks(rubiks);
    }
    return 0;
}
