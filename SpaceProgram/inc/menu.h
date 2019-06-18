#ifndef MENU_H
#define MENU_H

#define COLUMNSIZE 9

//#include "stm32f30x_rcc.h"
#include "ansi.h"
#include "30010_io.h"

void drawMenu();
void drawHelp();
int8_t updateArrow(char key, int8_t menu);
void runningMenu();
void gameOver(int8_t condition);


#endif
