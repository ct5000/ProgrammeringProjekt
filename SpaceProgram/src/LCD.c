#include "LCD.h"


/*  Function: lcdWriteString.
* -----------------------------------------------
* Writes a string to the lcd buffer..
*
* t[]; array of chars.
* buffer; An array representing the char show on the lcd.
* line; chosen line on the lcd.
* slice; Chosen slices on the lcd.
*
* returns; void.
*/
void lcdWriteString(char t[], uint8_t *buffer, int8_t line, int8_t slice){
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


void lcdUpdate(rollingtext_t *p,uint8_t * buffer){
    if (getAlienFlag() == 4){
        memset(buffer, 0x00, 512);
        (*p).slice--;
        lcdWriteString((*p).t, buffer, (*p).line, (*p).slice);
        resetAlienFlag();
    }
}

void initRolling(rollingtext_t *p, int8_t line, char * text){
    (*p).t=text;
    (*p).line=line;
    (*p).slice=127;
}


/*  Function: lcdUpdate.
* -----------------------------------------------
* Writes a bar on the lcd buffer.
*
* buffer; An array representing the char show on the lcd.
* line; chosen line on the lcd.
* slice; Chosen slices on the lcd.
*
* returns; void.
*/
void lcdWriteBar(char t[], uint8_t *buffer, int8_t line, int8_t slice){
    int i=0;
    int j=0;
    int c;
    int as;


    as = (int)t[i]-32;
    c = (((128*line) + slice + (5*i) + j));
    if ((c/128) == line && c >= 0) {
            buffer[c]= character_data[as][j];
        }

}


