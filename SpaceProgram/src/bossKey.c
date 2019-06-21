#include "bossKey.h"

void bossKey() {
    int8_t i, num;
    char key;
    color(15, 0);
    clrscr();
    printf("Compiling program:");
    while (key != 'b' && key != 'B') {
            if (uart_get_count() > 0) {
                key = uart_get_char();
            }
            for (i = 0; i < 100; i++) {
                    num = rand() % 2;
                    printf("%d", num);
            }
    }
}
