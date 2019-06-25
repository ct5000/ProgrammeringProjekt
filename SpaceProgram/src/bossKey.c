#include "bossKey.h"
/*
 * Function: bossKey
 * --------------------------
 * Runs a separate screen with random 1s and 0s until the user pushes on the b button.
 *
 * returns: void
 */


void bossKey() {
    int8_t num;
    char key;
    gotoxy(1,1);
    color(15, 0);
    clrscr();
    while (key != 'b' && key != 'B') {
            if (uart_get_count() > 0) {
                key = uart_get_char();
                uart_clear();
            }

            if (getBulletFlag() > 1) {
                    num = rand() % 2;
                    printf("%d", num);
                    resetBulletFlag();
            }
    }
}
