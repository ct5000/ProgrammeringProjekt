#include "LCD.h"


void lcd_write_string(char t[], char *buffer, int8_t line, int8_t slice){
    int i,j, c;
    int as;



    for (i=0; i<strlen(t);i++){
    as = (int)t[i]-32;

        for (j=0; j<5; j++){
            c = (((128*line) + slice + (5*i) + j));
            if ((c/128) == line && c >= 0) {
                buffer[c + 20]= character_data[as][j]; // add 20 to align to start
            }
        }

    }

}

void lcd_update(rollingtext_t *p,char * buffer){
    if (getFlag() == 4){
        memset(buffer, 0x00, 512);
        (*p).slice--;
        lcd_write_string((*p).t, &buffer, (*p).line, (*p).slice);
        rstFlag();
    }

}

void initRolling(rollingtext_t *p, int8_t line, char * text){
    (*p).t=text;
    (*p).line=line;
    (*p).slice=127;
}

