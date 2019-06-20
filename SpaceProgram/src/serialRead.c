#include "serialRead.h"
#include <string.h>

int i = 0;

char* serialRead(char *s){
    char *rs = calloc(256, sizeof(char));

    char c ;

    if (uart_get_count() > 0) {
        c = uart_get_char();
        s[i] = c;
        i++;
    }

    if (c == 0x0D) {
        s[i] = '\0';
        uart_clear();
        i = 0;
        rs = s;
        s = calloc(256, sizeof(char));
    }
    return rs;
}





