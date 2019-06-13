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
#endif

