
#ifndef LCD_H
#define LCD_H

#include "30010_io.h"
#include <string.h>
#include "charset.h"

typedef struct {
    int8_t slice;
    int8_t line;
    char *t;

}rollingtext_t;

void lcd_write_string(char t[], char *buffer, int8_t line, int8_t slice);
void lcd_update(rollingtext_t *p,char * buffer);
void initRolling(rollingtext_t *p, int8_t line, char * text);

#endif

