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
    color(15, 0);
    clrscr();
    gotoxy(1,1);
    while (key != 'b' && key != 'B') { //waits for the player to press b or B
            if (uart_get_count() > 0) { //gets user input if any
                key = uart_get_char();
                uart_clear();
            }
            if (getBulletFlag() > 1) { //slows the writing of 0s and 1s
                    num = rand() % 2;
                    printf("%d", num);
                    resetBulletFlag();
            }
    }
}
