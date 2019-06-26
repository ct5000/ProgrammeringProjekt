#include "menu.h"

/*
 * Function: bossKey
 * --------------------------
 * Draws the menu of the game in the middle with a little instruction for using it
 *
 * returns: void
 */
void drawMenu() {
    clrscr();
    gotoxy(TITLE_STARTX, TITLE_Y);
    writeS(COLUMNSIZE);
    writeP(COLUMNSIZE);
    writeA(COLUMNSIZE);
    writeC(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeBlank(COLUMNSIZE);
    writeR(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeS(COLUMNSIZE);
    writeC(COLUMNSIZE);
    writeU(COLUMNSIZE);
    writeE(COLUMNSIZE);
    gotoxy(MENU_X, 15);
    writeS(COLUMNSIZE);
    writeT(COLUMNSIZE);
    writeA(COLUMNSIZE);
    writeR(COLUMNSIZE);
    writeT(COLUMNSIZE);
    gotoxy(MENU_X, 27);
    writeH(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeL(COLUMNSIZE);
    writeP(COLUMNSIZE);
    gotoxy(ARROW_X, ARROW_Y1);
    drawArrow();
    gotoxy(INSTRUCTION_X, INSTRUCTION_Y);
    printf("Use w up and s to choose menu point and hit enter to continue");

}

/*
 * Function: updateArrow
 * --------------------------
 * Updates the menu arrow according to the user in put and draws it in the right place
 *
 * key: the key stroke from the user
 * menu: the current menu position
 *
 * returns: the number for the menu it is on
 */
int8_t updateArrow(char key, int8_t menu) {
    if (key == 's') {
            if (menu == 1) {
                    gotoxy(ARROW_X, ARROW_Y1);
                    printf("    ");
                    gotoxy(ARROW_X, ARROW_Y2);
                    drawArrow();
            }
            return 2;
    }
    else if (key == 'w') {
            if (menu == 2) {
                    gotoxy(ARROW_X, ARROW_Y2);
                    printf("    ");
                    gotoxy(ARROW_X, ARROW_Y1);
                    drawArrow();
            }
            return 1;
    }
    return menu;
}

/*
 * Function: drawHelp
 * --------------------------
 * Draws the help menu for the game
 *
 * returns: void
 */
void drawHelp() {
    clrscr();
    gotoxy(TITLE_STARTX, 15);
    printf("The purpose of SPACE RESQUE is to escape the planet. At the same time aliens are attacking you to hinder your escape.");
    gotoxy(TITLE_STARTX, 16);
    printf("Your space ship does not have the necessary fuel to leave the gravity field of the planet. Luckily the planet's underground");
    gotoxy(TITLE_STARTX, 17);
    printf("is full of it, you just have to drill it up using your drill. To maneuver your ship use W, A and D. Be aware of the gravity");
    gotoxy(TITLE_STARTX, 18);
    printf("pulling you down. To drill for fuel press E. Besides fuel you can get a shield or some POWER BULLETS. To aim your ships");
    gotoxy(TITLE_STARTX, 19);
    printf("canon use the potentiometer on the micro controller. To fire press SPACE. Have been so lucky to get some POWER BULLETS use them on G.");
    gotoxy(TITLE_STARTX, 20);
    printf("These bullets can go through multiple enemies. Good luck");
    gotoxy(INSTRUCTION_X, INSTRUCTION_Y);
    printf("Press ENTER to return to the menu");
}

/*
 * Function: runningMenu
 * --------------------------
 * Runs the menu and updates the graphics according to the user inputs.
 *
 * returns: void
 */
void runningMenu() {
    int menuArrow= 1;
    int menu = 1;
    char keyStroke;
    drawMenu();
    //Keeps the player in the menu until it hits enter at START
    while(menu) {
        //reads user input if any
        if (uart_get_count() > 0) { //reads user input if any
                keyStroke = uart_get_char();
                uart_clear();
            }
        //enters bossKey if b
        if (keyStroke == 'b') {
                bossKey();
                runningMenu();
                break;
        }
        //checks if in help menu and the user wants to return
        else if (menu == 2 && keyStroke == 0x0D) {
                menu = 1;
                drawMenu();
                menuArrow = 1;
        }
        //checks if in main menu
        else if (menu == 1) {
            menuArrow = updateArrow(keyStroke, menuArrow);
            if (keyStroke == 0x0D) {
                //checks if enter should get in to help menu
                if (menuArrow == 2) {
                    drawHelp();
                    menu = 2;
                }
                //check if help should end the menu
                else {
                    menu = 0;
                }
            }
        }
        keyStroke = ' ';
    }
}

/*
 * Function: gameOver
 * --------------------------
 * Draws the game over menu with message. It stays there until the user press enter
 *
 * condition: The condition which terminated the game
 * score: the players score
 * level: the level the player was on
 *
 * returns: void
 */
void gameOver(int8_t condition, uint16_t score, uint8_t level) {
    char user;
    color(7,0);
    clrscr();
    gotoxy(TITLE_STARTX,TITLE_Y);
    writeG(COLUMNSIZE);
    writeA(COLUMNSIZE);
    writeM(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeBlank(COLUMNSIZE);
    writeO(COLUMNSIZE);
    writeV(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeR(COLUMNSIZE);
    gotoxy(70, 15);
    switch (condition) {
    case 2: //The player ran out of fuel
        printf("You ran out of fuel and can no longer get off the planet. The aliens will be here soon... YOU LOST");
        break;
    case 3: //The player got killed
        printf("The aliens have overpowered you and your spaceship has been destroyed. YOU LOST");
        break;
    case 4: //score is 0
        printf("You're too slow. YOU LOST");
        break;

    default:
        printf("ERROR");
    }
    gotoxy(INSTRUCTION_X, INSTRUCTION_Y);
    printf("Press enter to return to the menu");
    gotoxy(LEVEL_SCORE, 25);
    printf("Score: %06d", score);
    gotoxy(LEVEL_SCORE, 26);
    printf("Level: %06d", level);
    while(1) {
            if (uart_get_count() > 0) { //reads user input if any
                user = uart_get_char();
                uart_clear();
            }
            //Stop the game over screen if user press enter
            if (user == 0x0D) {
                    uart_clear();
                    break;
            }
            //Enters bossKey function if the user press b
            else if (user == 'b') {
                    bossKey();
                    gameOver(condition, score, level);
                    break;
            }
            user = ' ';
    }

}

/*
 * Function: nextLevel
 * --------------------------
 * Draws the next level menu with message. It stays there until the user press enter
 *
 * score: the players score
 * level: the level the player was on
 *
 * returns: void
 */
void nextLevel(uint16_t score, uint8_t level){
    color(7,0);
    char user;
    clrscr();
    gotoxy(TITLE_STARTX, TITLE_Y);
    writeN(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeX(COLUMNSIZE);
    moveCursorRight(1);
    writeT(COLUMNSIZE);

    writeBlank(COLUMNSIZE);

    writeL(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeV(COLUMNSIZE);
    writeE(COLUMNSIZE);
    writeL(COLUMNSIZE);

    gotoxy(INSTRUCTION_X, INSTRUCTION_Y);
    printf("Press enter to start");
    gotoxy(LEVEL_SCORE, 25);
    printf("Score: %06d", score);
    gotoxy(LEVEL_SCORE, 26);
    printf("Level: %06d", level);

    while(1) {
            if (uart_get_count() > 0) { //reads user input if any
                user = uart_get_char();
                uart_clear();
            }
            //Ends the while loop if enter
            if (user == 0x0D) {
                    uart_clear();
                    break;
            }
            //Enter bossKey function if user press b
            else if (user == 'b') {
                    bossKey();
                    nextLevel( score, level);
                    break;
            }
            user = ' ';
    }

}



