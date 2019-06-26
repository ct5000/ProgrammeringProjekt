
#include "ansi.h"
/*
 * Function: clrscr
 * --------------------------
 * Clears the screen of the terminal
 *
 *
 * returns: void
 */

void clrscr(){ // clears the terminal
    printf("%c[2J",ESC);
}

/*
 * Function: clreol
 * --------------------------
 * Clears a line of the terminal
 *
 *
 * returns: void
 */
void clreol(){  // clears the rest of a line // bruges ikke
    printf("%c[0K",ESC);
}

/*
 * Function: gotoxy
 * --------------------------
 * Moves the cursor to a specific location
 *
 * x: x-coordinate to move the cursor to
 * y: y-coordinate to move the cursor to
 *
 * returns: void
 */
void gotoxy(int x, int y){ // moves to cursor to a x, y position
    printf("%c[%d;%dH",ESC,y,x);
}

/*
 * Function: deleteSymbol
 * --------------------------
 * Deletes a single character
 *
 * x: x-coordinate for the character to delete
 * y: y-coordinate for the character to delete
 *
 *
 * returns: void
 */
void deleteSymbol(int x, int y){

    gotoxy(x,y);
    printf(" ");

}

/*
 * Function: box
 * --------------------------
 * Draws a symbol on a specific coordinate
 *
 * x1: x-coordinate for symbol
 * y1: y-coordinate for symbol
 * sym: symbol to draw
 *
 * returns: void
 */
void drawSymbol(int x, int y, char sym){
    gotoxy(x,y);
    printf("%c",sym);
}
/*
 * Function: writeS
 * --------------------------
 * Draws an S in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeS(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(2);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeP
 * --------------------------
 * Draws an P in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeP(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(2);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

void drawVerticalRight(int8_t spaces) {
    int i;
    for (i = 0; i < spaces; i++) {
            printf("%c", LETTER_BLOCK);
    }
}

/*
 * Function: writeA
 * --------------------------
 * Draws an A in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeA(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    moveCursorUp(sizeColumn/3 + 2);
    moveCursorLeft(1);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(2);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeC
 * --------------------------
 * Draws an C in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeC(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < (sizeColumn/3) * 2 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeE
 * --------------------------
 * Draws an E in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeE(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
    }
    moveCursorLeft(sizeColumn - 1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeR
 * --------------------------
 * Draws an R in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeR(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(2);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorRight(sizeColumn/2 - 2);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeQ
 * --------------------------
 * Draws an Q in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeQ(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn-2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorDown(1);
    printf("%c", LETTER_BLOCK);
    moveCursorUp(1);
    moveCursorLeft(3);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(2);
    }
    printf("%c", LETTER_BLOCK);
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeBlank
 * --------------------------
 * Draws a blank space in width for big letters
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeBlank(int8_t sizeColumn) {
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeU
 * --------------------------
 * Draws an U in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeU(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn-1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorUp(1);
    for (i = 0; i < sizeColumn-1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);

}

/*
 * Function: writeT
 * --------------------------
 * Draws an T in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeT(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", LETTER_BLOCK);
    }
    moveCursorLeft(sizeColumn/3 + 1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn-1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(1);
            moveCursorDown(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeH
 * --------------------------
 * Draws an H in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeH(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn / 2; i ++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorDown(1);
    moveCursorLeft(1);
    for (i = 0; i < sizeColumn / 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    moveCursorUp(sizeColumn / 2 + 1);
    moveCursorRight(1);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorUp(1);
    moveCursorLeft(1);
    for (int i = 0; i < sizeColumn / 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    moveCursorDown(sizeColumn / 2 + 5);
    for (int i = 0; i < sizeColumn / 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeL
 * --------------------------
 * Draws an L in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeL(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn-1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeO
 * --------------------------
 * Draws an O in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeO(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(2);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorUp(1);
    for (i = 0; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    returnCursor();
    moveCursorRight((sizeColumn));
}

/*
 * Function: writeG
 * --------------------------
 * Draws an G in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeG(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", LETTER_BLOCK);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(1);
    moveCursorUp(1);
    for (i = 0; i < sizeColumn / 3; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorUp(1);
            moveCursorLeft(1);
    }
    printf("%c", LETTER_BLOCK);
    moveCursorLeft(2);
    for (i = 0; i < 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(2);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeM
 * --------------------------
 * Draws an M in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeM(int8_t sizeColumn) {
    int i;
    saveCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn - 1; i++) {
        printf("%c", LETTER_BLOCK);
        moveCursorLeft(1);
        moveCursorDown(1);
    }
    returnCursor();
    for (i = 0; i < sizeColumn / 3 + 1; i++) {
        printf("%c", LETTER_BLOCK);
        moveCursorDown(1);

    }
    moveCursorUp(1);
    for (i = 0; i < sizeColumn / 3 + 1; i++) {
        printf("%c", LETTER_BLOCK);
        moveCursorUp(1);
    }
    moveCursorDown(1);
    for (i = 0; i < sizeColumn - 1; i++) {
        moveCursorDown(1);
        moveCursorLeft(1);
        printf("%c", LETTER_BLOCK);
    }
    returnCursor();
    moveCursorRight(sizeColumn);

}

/*
 * Function: writeV
 * --------------------------
 * Draws an V in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeV(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn / 2 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(1);
            moveCursorDown(1);
    }
    for (i = 0; i < sizeColumn / 2 - 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorDown(1);
    }
    for (i = 0; i < sizeColumn / 2; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorUp(1);
    }
    moveCursorLeft(1);
    for (i = 0; i < sizeColumn / 2 + 1; i++) {
            printf("%c", LETTER_BLOCK);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeX
 * --------------------------
 * Draws an X in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeX(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i=0; i<sizeColumn; i++){
        printf("%c",LETTER_BLOCK);
        moveCursorDown(1);
    }


    returnCursor();
    moveCursorRight(sizeColumn - 1);
    for (i=0; i<sizeColumn; i++){
        printf("%c",LETTER_BLOCK);
        moveCursorDown(1);
        moveCursorLeft(2);
    }


    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: writeN
 * --------------------------
 * Draws an N in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void writeN(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i=0; i<sizeColumn;i++){
        printf("%c",LETTER_BLOCK);
        moveCursorDown(1);
        moveCursorLeft(1);
    }
    returnCursor();
    for (i=0; i<sizeColumn-2; i++){
        printf("%c",LETTER_BLOCK);
        moveCursorDown(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn-2);
    for (i=0; i<sizeColumn;i++){
        printf("%c",LETTER_BLOCK);
        moveCursorDown(1);
        moveCursorLeft(1);
}

    returnCursor();
    moveCursorRight(sizeColumn);
}

/*
 * Function: deleteLetter
 * --------------------------
 * Deletes a letter in a big size
 *
 * sizeColumn: size of the width for the letter with ending space
 *
 * returns: void
 */
void deleteLetter(int8_t sizeColumn) { // bruges ikke
    int i, j;
    saveCursor();
    for(i = 0; i< sizeColumn + 1; i++) {
            for (j = 0; j < sizeColumn; j++) {
                    printf(" ");
            }
    }
}

/*
 * Function: drawArrow
 * --------------------------
 * Draws an arrow
 *
 * returns: void
 */
void drawArrow() {
    printf("--->");
}

/*
 * Function: saveCursor
 * --------------------------
 * Saves position of the cursor
 *
 * returns: void
 */
void saveCursor() {
    printf("%c[s", ESC);
}

/*
 * Function: returnCursor
 * --------------------------
 * Returns to the saved position of the cursor
 *
 * returns: void
 */
void returnCursor() {
    printf("%c[u", ESC);
}

/*
 * Function: moveCursorRight
 * --------------------------
 * Moves the cursor i positions to the right
 *
 * i: the number of positions to move the cursor
 *
 * returns: void
 */
void moveCursorRight(int i) {
    printf("%c[%dC", ESC, i);
}

/*
 * Function: moveCursorLeft
 * --------------------------
 * Moves the cursor i positions to the left
 *
 * i: the number of positions to move the cursor
 *
 * returns: void
 */
void moveCursorLeft(int i) {
    printf("%c[%dD", ESC, i);
}

/*
 * Function: moveCursorUp
 * --------------------------
 * Moves the cursor i positions up
 *
 * i: the number of positions to move the cursor
 *
 * returns: void
 */
void moveCursorUp(int i) {
    printf("%c[%dA", ESC, i);
}

/*
 * Function: moveCursorDown
 * --------------------------
 * Moves the cursor i positions down
 *
 * i: the number of positions to move the cursor
 *
 * returns: void
 */
void moveCursorDown(int i) {
    printf("%c[%dB", ESC, i);
}

/*
 * Function: drawAlien
 * --------------------------
 * Draws an alien to the terminal
 *
 * x: x-coordinate for the alien's center
 * y: y-coordinate for the alien's center
 *
 * returns: void
 */
void drawAlien(int x, int y) {
    gotoxy(x - 1,y - 1);
    printf("%c%c%c", 201, 207, 187);
    gotoxy(x - 1, y);
    printf("%c%c%c", 40, 178, 41);
    gotoxy(x - 1, y + 1);
    printf("%c%c%c", 242, 176, 242);
}

/*
 * Function: drawShip
 * --------------------------
 * Draws a spaceship to the terminal
 *
 * x: x-coordinate for the spaceship's center
 * y: y-coordinate for the spaceship's center
 *
 * returns: void
 */
void drawShip(int x, int y, int shield) {
    if (shield){
        fgcolor(4);
        gotoxy(x - 1,y - 1);
        printf("%c%c%c", 217, 65, 192);
        gotoxy(x - 1, y);
        printf("%c%c%c", 219, 206, 219);
        fgcolor(1);
        gotoxy(x - 1, y + 1);
        printf("%c%c%c", 201, 190, 187);
    }
    else{
        fgcolor(1);
        gotoxy(x - 1,y - 1);
        printf("%c%c%c", 217, 65, 192);
        gotoxy(x - 1, y);
        printf("%c%c%c", 219, 206, 219);
        gotoxy(x - 1, y + 1);
        printf("%c%c%c", 201, 190, 187);
    }
    fgcolor(7);
}

/*
 * Function: deleteAlien
 * --------------------------
 * Deletes an alien or spaceship from the terminal
 *
 * x: x-coordinate for the alien's center
 * y: y-coordinate for the alien's center
 *
 * returns: void
 */
void deleteAlien(int x, int y) {
    int i, j;
    for (i = x - 1; i <= x + 1; i++) {
            for (j = y - 1; j <= y + 1; j++) {
                    deleteSymbol(i, j);
            }
    }
}

/*
 * Function: fgcolor
 * --------------------------
 * Changes the foreground color for the terminal window
 *
 * foreground: the choice for the foreground color
 *
 * returns: void
 */
void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

/*
 * Function: bgcolor
 * --------------------------
 * Changes the background color for the terminal window
 *
 * background: the choice for the background color
 *
 * returns: void
 */
void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

/*
 * Function: color
 * --------------------------
 * Changes the foreground and background color for the terminal window
 *
 * foreground: the choice for the foreground color
 * background: the choice for the background color
 *
 * returns: void
 */
void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

/*
 * Function: resetbgcolor
 * --------------------------
 * Resets the terminal to gray on black text without underline, blink or reverse
 *
 * returns: void
 */
void resetbgcolor() {
  printf("%c[m", ESC);
}

