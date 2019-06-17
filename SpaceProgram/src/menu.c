#include "menu.h"

/*
Draws the menu of the game in the middle. It takes no parameters and has no return value.
*/
void drawMenu() {
    clrscr();
    gotoxy(70, 3);
    writeS(COLUMNSIZE);
    writeP(COLUMNSIZE);
    writeA(COLUMNSIZE);
    writeC(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeBlank(COLUMNSIZE);
    writeR(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeS(COLUMNSIZE);
    writeQ(COLUMNSIZE);
    writeU(COLUMNSIZE);
    writeE(COLUMNSIZE);
    gotoxy(88, 15);
    writeS(COLUMNSIZE);
    writeT(COLUMNSIZE);
    writeA(COLUMNSIZE);
    writeR(COLUMNSIZE);
    writeT(COLUMNSIZE);
    gotoxy(88, 27);
    writeH(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeL(COLUMNSIZE);
    writeP(COLUMNSIZE);
    gotoxy(83, 19);
    drawArrow();
    gotoxy(53, 40);
    printf("Use w up and s to choose menu point and hit enter to continue");

}

int8_t updateArrow(char key, int8_t menu) {
    if (key == 's') {
            if (menu == 1) {
                    gotoxy(83, 19);
                    printf("    ");
                    gotoxy(83, 31);
                    drawArrow();
            }
            return 2;
    }
    else if (key == 'w') {
            if (menu == 2) {
                   gotoxy(83, 31);
                    printf("    ");
                    gotoxy(83, 19);
                    drawArrow();
            }
            return 1;
    }
    return menu;
}

void drawHelp() {
    clrscr();
    gotoxy(70, 15);
    printf("The purpose of SPACE RESQUE is to escape the planet. At the same time aliens are attacking you to hinder your escape.");
    gotoxy(70, 16);
    printf("Your space ship does now have the necessary fuel to leave the gravity field of the planet. Luckily the planet's underground");
    gotoxy(70, 17);
    printf("is full of it, you just have to drill it up using your drill. To maneuver your ship use W, A and D. Be aware of the gravity");
    gotoxy(70, 18);
    printf("pulling you down. To drill for fuel press E. To aim your ships canon use the potentiometer on the micro controller. To fire");
    gotoxy(70, 19);
    printf("press SPACE. Good luck");
    gotoxy(83, 50);
    printf("Press ENTER to return to the menu");
}

void runningMenu() {
    int menuArrow= 1;
    int menu = 1;
    char keyStroke;
    drawMenu();
    //Keeps the player in the menu until it hits enter at START
    while(menu) {
        keyStroke = uart_get_char();
        if (menu == 2 && keyStroke == 0x0D) {
                menu = 1;
                drawMenu();
                menuArrow = 1;
        }
        else if (menu == 1) {
            menuArrow = updateArrow(keyStroke, menuArrow);
            if (keyStroke == 0x0D) {
                if (menuArrow == 2) {
                    drawHelp();
                    menu = 2;
                }
                else {
                    menu = 0;
                }
            }
        }
    }
}
