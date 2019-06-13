#define ESC 0x1B
#include "ansi.h"

void clrscr(){
    printf("%c[2J",ESC);
}
void clreol(){
    printf("%c[0K",ESC);
}
void gotoxy(int x, int y){
    printf("%c[%d;%dH",ESC,y,x);
}
void underline(uint8_t on){
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

