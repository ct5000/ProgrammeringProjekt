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
    int ansiChar;
    for (i=0; i<strlen(t);i++){ //goes through letters in the string
        ansiChar = (int)t[i]-32;
        for (j=0; j<LETTER_WIDTH; j++){ //goes through each column in the letter
            c = (((TOTAL_SLICES*line) + slice + (LETTER_WIDTH*i) + j));
            if ((c/TOTAL_SLICES) == line && c >= 0) { //checks if on the line
                buffer[c]= character_data[ansiChar][j];
            }
        }
    }
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
void lcdWriteBar(int on, uint8_t *buffer, int8_t line, int8_t slice){
    int c;
    char barType;
    if (on) {
            barType = FULL_BAR;
    }
    else {
            barType = EMPTY_BAR;
    }
    c = (TOTAL_SLICES*line) + slice;
    if ((c/TOTAL_SLICES) == line && c >= 0) {
            buffer[c]= barType;
        }

}


