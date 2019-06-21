
#ifndef LCD_H
#define LCD_H

#include "30010_io.h"
#include <string.h>
#include "charset.h"
#include "mbed.h"

typedef struct {
    int8_t slice;
    int8_t line;
    char *t;

}rollingtext_t;

void lcdWriteString(char t[], uint8_t *buffer, int8_t line, int8_t slice);
void lcdUpdate(rollingtext_t *p,uint8_t * buffer);
void initRolling(rollingtext_t *p, int8_t line, char * text);
void lcdWriteBar(char t[], uint8_t *buffer, int8_t line, int8_t slice);

#endif

