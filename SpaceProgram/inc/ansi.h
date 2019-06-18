/* Includes ------------------------------------------------------------------*/
#include "stm32f30x_conf.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef _ANSI_H_
#define _ANSI_H_

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);

void clrscr();
void clreol();
void gotoxy(int x, int y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void box(int x1, int y1, int x2, int y2, int design, char windowName[]);
void deleteSymbol(int x, int y);
void drawSymbol(int x, int y, char sym);

void saveCursor();
void returnCursor();
void moveCursorRight(int i);
void moveCursorLeft(int i);
void moveCursorUp(int i);
void moveCursorDown(int i);

void writeA(int8_t sizeColumn);
void writeP(int8_t sizeColumn);
void writeS(int8_t sizeColumn);
void writeC(int8_t sizeColumn);
void writeE(int8_t sizeColumn);
void writeR(int8_t sizeColumn);
void writeQ(int8_t sizeColumn);
void writeBlank(int8_t sizeColumn);
void writeU(int8_t sizeColumn);
void writeT(int8_t sizeColumn);
void writeH(int8_t sizeColumn);
void writeL(int8_t sizeColumn);
void writeO(int8_t sizeColumn);
void writeG(int8_t sizeColumn);
void writeM(int8_t sizeColumn);
void writeV(int8_t sizeColumn);
void deleteLetter(int8_t sizeColumn);

void drawAlien(int x, int y);
void drawShip(int x, int y);
void deleteAlien(int x, int y);

void drawArrow();

#endif

