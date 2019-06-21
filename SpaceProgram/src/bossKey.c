#include "bossKey.h"
/*
 * Function: bossKey
 * --------------------------
 * Runs a separate screen with random 1s and 0s until the user pushes on the b button.
 *
 * returns: void
 */


void bossKey() {
    int8_t i, num;
    char key;
    color(15, 0);
    clrscr();
    while (key != 'b' && key != 'B') {
            if (uart_get_count() > 0) {
                key = uart_get_char();
                uart_clear();
            }
            for (i = 0; i < 8; i++) {
                    num = rand() % 2;
                    printf("%d", num);
            }
    }
}
