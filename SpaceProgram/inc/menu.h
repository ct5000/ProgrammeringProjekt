#ifndef MENU_H
#define MENU_H

#include "stm32f30x_rcc.h"
#include "ansi.h"
#include "30010_io.h"
#include "bossKey.h"

#define COLUMNSIZE 9
#define TITLE_STARTX 70
#define TITLE_Y 3
#define INSTRUCTION_X 70
#define INSTRUCTION_Y 40
#define MENU_X 88
#define ARROW_X 83
#define ARROW_Y1 19
#define ARROW_Y2 31
#define LEVEL_SCORE 110


void drawMenu();
void drawHelp();
int8_t updateArrow(char key, int8_t menu);
void runningMenu();
void gameOver(int8_t condition, uint16_t score, uint8_t level);
void nextLevel(uint16_t score, uint8_t level);

#endif
