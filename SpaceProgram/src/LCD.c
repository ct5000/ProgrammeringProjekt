#include "LCD.h"


void lcd_write_string(char t[], uint8_t *buffer, int8_t line, int8_t slice){
    int i,j, c;
    int as;

    for (i=0; i<strlen(t);i++){
    as = (int)t[i]-32;

        for (j=0; j<5; j++){
            c = (((128*line) + slice + (5*i) + j));
            if ((c/128) == line && c >= 0) {
                buffer[c]= character_data[as][j]; // add 20 to align to start
            }
        }
    }
}

void lcd_update(rollingtext_t *p,uint8_t * buffer){
    if (getAlienFlag() == 4){
        memset(buffer, 0x00, 512);
        (*p).slice--;
        lcd_write_string((*p).t, buffer, (*p).line, (*p).slice);
        resetAlienFlag();
    }
}

void initRolling(rollingtext_t *p, int8_t line, char * text){
    (*p).t=text;
    (*p).line=line;
    (*p).slice=127;
}


////////// skal rettes ////////
void lcd_write_bar(char t[], uint8_t *buffer, int8_t line, int8_t slice){
    int i,j, c;
    int as;

    for (i=0; i<strlen(t);i++){
    as = (int)t[i]-32;

        for (j=0; j<1; j++){
            c = (((128*line) + slice + (5*i) + j));
            if ((c/128) == line && c >= 0) {
                buffer[c]= character_data[as][j];
            }
        }
    }
}


