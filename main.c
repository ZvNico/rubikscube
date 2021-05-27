#include <stdio.h>
#include "src/enum_types/enum_types.h"
#include "src/rubiks/rubiks.h"

int main() {
    void (*menu_func[])(Rubiks **) = {&init_rubiks, &blank_rubiks, &init_rubiks, &scramble_rubiks, &fill_rubiks,
                                      &move_rubiks};
    Rubiks **rubiks = create_rubiks();
    int i = 0;
    while (i != -1) {
        do {
            printf("================================================================\n");
            printf("||      1: Init             2: Blank          3: Reset        ||\n");
            printf("||      4: Scramble         5: Fill           6: Play         ||\n");
            printf("||                         -1: Quit                           ||\n");
            printf("================================================================\n");
            scanf("%d", &i);
        } while (i != 1 && i != 2 && i != 3 && i != 4 && i != 5 && i != 6 && i != -1);
        printf("%d\n", i);
        if (i != -1) {
            menu_func[i - 1](rubiks);
            display_rubiks(rubiks);
        }
    }
    return 0;
}
