#define ESC 0x1B
#include "ansi.h"


void clrscr(){ // clears the terminal
    printf("%c[2J",ESC);
}
void clreol(){  // clears the rest of a line
    printf("%c[0K",ESC);
}
void gotoxy(int x, int y){ // moves to cursor to a x, y position
    printf("%c[%d;%dH",ESC,y,x);
}
void underline(uint8_t on){ // makes a underline
    int u;
    u = on ? 4 : 24;
    printf("%c[%dm",ESC,u);
}
void blink(uint8_t on){
    int bli;
    bli = on ? 5 : 25;
    printf("%c[%dm",ESC,bli);
}
void inverse(uint8_t on){
    int inv;
    inv = on ? 7 : 27;
    printf("%c[%dm",ESC,inv);
}
void box(int x1, int y1, int x2, int y2, int design, char name[]){
    int l = x2-x1;
    int b = y2-y1;
    int i, j;
    int x= x1;
    int y= y1;
    int lodret, vandret;
    int x1y1, x1y2, x2y1, x2y2;


    char windowName[l-1];
    for ( i=0; i<l-2; i++){
          windowName[i]= name[i];
          windowName[i] = i<strlen(name) ? name[i] : ' ';
          }
    windowName[i-2] = '\0';
    gotoxy(x1+3,y1);

    color(7,0);
    printf("%s", windowName);
    color(0,7);

    gotoxy(x1,y1);
    lodret = design == 1 ? 179 : 186;
    for (i=0; i<2; i++){
        for (j=0; j<=b; j++){
            printf("%c",lodret);
            gotoxy(x,++y);
        }
        gotoxy(x2,y1);
        y=y1;
        x = x2;
}

//Vandret
    gotoxy(x1,y2);
    vandret = design == 1 ? 196 : 205;
    for (i=0; i<l;i++){
        printf("%c", vandret );
    }
    //gotoxy(x1,y1);
    //for (i=0; i<l;i++){
     //   printf("%c", vandret );
//}

    x1y1 = design == 1 ? 218 : 201;
    gotoxy(x1,y1);
    printf("%c",x1y1);
    x2y2 = design == 1 ? 217 : 188;
    gotoxy(x2,y2);
    printf("%c",x2y2);
    x1y2 = design == 1 ? 192 : 200;
    gotoxy(x1,y2);
    printf("%c",x1y2);
    x2y1 = design == 1 ? 191 : 187;
    gotoxy(x2,y1);
    printf("%c",x2y1);

    printf("%c[H",ESC);

}
void deleteSymbol(int x, int y){

    gotoxy(x,y);
    printf(" ");

}
void drawSymbol(int x, int y, char sym){

    gotoxy(x,y);
    printf("%c",sym);


}
void writeS(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 192);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 191);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 217);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 2; i++) {
            printf("%c", 196);
            moveCursorLeft(2);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeP(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 191);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 217);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", 196);
            moveCursorLeft(2);
    }
    printf("%c", 195);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeA(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 191);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 180);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3 + 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    moveCursorUp(sizeColumn/3 + 2);
    moveCursorLeft(1);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", 196);
            moveCursorLeft(2);
    }
    printf("%c", 195);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeC(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < (sizeColumn/3) * 2 + 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 192);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeE(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 195);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    moveCursorLeft(sizeColumn - 1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 192);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeR(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 191);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 217);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", 196);
            moveCursorLeft(2);
    }
    printf("%c", 195);
    moveCursorRight(sizeColumn/2 - 2);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", 92);
            moveCursorDown(1);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    moveCursorDown(1);
    for (i = 0; i < sizeColumn/3 + 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeQ(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 191);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn-1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 217);
    moveCursorDown(1);
    printf("%c", 92);
    moveCursorUp(1);
    moveCursorLeft(3);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
            moveCursorLeft(2);
    }
    printf("%c", 192);
    returnCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn - 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeBlank(int8_t sizeColumn) {
    moveCursorRight(sizeColumn);
}
void writeU(int8_t sizeColumn) {
    int i;
    for (i = 0; i < sizeColumn; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 192);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 217);
    moveCursorLeft(1);
    moveCursorUp(1);
    for (i = 0; i < sizeColumn; i++) {
            printf("%c", 179);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    moveCursorRight(1);
    moveCursorDown(1);

}
void writeT(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 196);
    }
    printf("%c", 194);
    for (i = 0; i < sizeColumn/3; i++) {
            printf("%c", 196);
    }
    moveCursorLeft(sizeColumn/3 + 1);
    moveCursorDown(1);
    for (i = 0; i < sizeColumn; i++) {
            printf("%c", 179);
            moveCursorLeft(1);
            moveCursorDown(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeH(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn / 2; i ++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 195);
    moveCursorDown(1);
    moveCursorLeft(1);
    for (i = 0; i < sizeColumn / 2; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    moveCursorUp(sizeColumn / 2 + 1);
    moveCursorRight(1);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    printf("%c", 180);
    moveCursorUp(1);
    moveCursorLeft(1);
    for (int i = 0; i < sizeColumn / 2; i++) {
            printf("%c", 179);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    moveCursorDown(sizeColumn / 2 + 4);
    for (int i = 0; i < sizeColumn / 2; i++) {
            printf("%c", 179);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeL(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 192);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 196);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeO(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 191);
    moveCursorLeft(1);
    moveCursorDown(1);
    for (i= 0; i< sizeColumn - 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 217);
    moveCursorLeft(2);
    for (i = 0; i < sizeColumn - 3; i++) {
            printf("%c", 196);
            moveCursorLeft(2);
    }
    printf("%c", 192);
    moveCursorLeft(1);
    moveCursorUp(1);
    for (i = 0; i < sizeColumn - 1; i++) {
            printf("%c", 179);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    returnCursor();
    moveCursorRight((sizeColumn));
}
void writeG(int8_t sizeColumn) {
    int i;
    saveCursor();
    printf("%c", 218);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    returnCursor();
    moveCursorDown(1);
    for (i = 1; i < sizeColumn - 1; i++) {
            printf("%c", 179);
            moveCursorDown(1);
            moveCursorLeft(1);
    }
    printf("%c", 192);
    for (i = 1; i < sizeColumn - 2; i++) {
            printf("%c", 196);
    }
    printf("%c", 217);
    moveCursorLeft(1);
    moveCursorUp(1);
    for (i = 0; i < sizeColumn / 3; i++) {
            printf("%c", 179);
            moveCursorUp(1);
            moveCursorLeft(1);
    }
    printf("%c", 191);
    moveCursorLeft(2);
    for (i = 0; i < 2; i++) {
            printf("%c", 196);
            moveCursorLeft(2);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}
void writeM(int8_t sizeColumn) {
    int i;
    saveCursor();
    moveCursorDown(1);
    for (i = 0; i < sizeColumn - 1; i++) {
        printf("%c", 179);
        moveCursorLeft(1);
        moveCursorDown(1);
    }
    returnCursor();
    for (i = 0; i < sizeColumn / 3 + 1; i++) {
        printf("%c", 92);
        moveCursorDown(1);

    }
    moveCursorUp(1);
    for (i = 0; i < sizeColumn / 3 + 1; i++) {
        printf("%c", 47);
        moveCursorUp(1);
    }
    moveCursorDown(1);
    for (i = 0; i < sizeColumn - 1; i++) {
        moveCursorDown(1);
        moveCursorLeft(1);
        printf("%c", 179);
    }
    returnCursor();
    moveCursorRight(sizeColumn);

}
void writeV(int8_t sizeColumn) {
    int i;
    saveCursor();
    for (i = 0; i < sizeColumn / 2 + 1; i++) {
            printf("%c", 179);
            moveCursorLeft(1);
            moveCursorDown(1);
    }
    for (i = 0; i < sizeColumn / 2 - 1; i++) {
            printf("%c", 92);
            moveCursorDown(1);
    }
    for (i = 0; i < sizeColumn / 2; i++) {
            printf("%c", 47);
            moveCursorUp(1);
    }
    moveCursorLeft(1);
    for (i = 0; i < sizeColumn / 2 + 1; i++) {
            printf("%c", 179);
            moveCursorLeft(1);
            moveCursorUp(1);
    }
    returnCursor();
    moveCursorRight(sizeColumn);
}


void deleteLetter(int8_t sizeColumn) {
    int i, j;
    saveCursor();
    for(i = 0; i< sizeColumn + 1; i++) {
            for (j = 0; j < sizeColumn; j++) {
                    printf(" ");
            }
    }
}

void drawArrow() {
    printf("--->");
}

void saveCursor() {
    printf("%c[s", ESC);
}
void returnCursor() {
    printf("%c[u", ESC);
}
void moveCursorRight(int i) {
    printf("%c[%dC", ESC, i);
}
void moveCursorLeft(int i) {
    printf("%c[%dD", ESC, i);
}
void moveCursorUp(int i) {
    printf("%c[%dA", ESC, i);
}
void moveCursorDown(int i) {
    printf("%c[%dB", ESC, i);
}

void drawAlien(int x, int y) {
    gotoxy(x - 1,y - 1);
    printf("%c%c%c", 201, 207, 187);
    gotoxy(x - 1, y);
    printf("%c%c%c", 40, 178, 41);
    gotoxy(x - 1, y + 1);
    printf("%c%c%c", 242, 176, 242);
}
void drawShip(int x, int y) {
    fgcolor(1);
    gotoxy(x - 1,y - 1);
    printf("%c%c%c", 217, 65, 192);
    gotoxy(x - 1, y);
    printf("%c%c%c", 219, 206, 219);
    gotoxy(x - 1, y + 1);
    printf("%c%c%c", 201, 190, 187);
    fgcolor(0);
}

void deleteAlien(int x, int y) {
    int i, j;
    for (i = x - 1; i <= x + 1; i++) {
            for (j = y - 1; j <= y + 1; j++) {
                    deleteSymbol(i, j);
            }
    }
}

void drawPowerBullet(int x, int y) {
    gotoxy(x, y);
    printf("%c%c", 218, 191);
    moveCursorDown(1);
    moveCursorLeft(2);
    printf("%c%c", 192, 217);
}

void deletePowerBullet(int x, int y) {
    int i, j;
    for (i = x; i <= x + 1; i++) {
            for(j = y; j <= y + 1; j++) {
                    deleteSymbol(i, j);
            }
    }
}


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

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

