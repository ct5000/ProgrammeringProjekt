#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ansi.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 66
#define GROUND_HEIGHT 56
#define NUMBER_BOXES 10
#define BGCOLORS_MAX 7
#define LANDSCAPE_CHAR 176
#define FUEL_MIN 3
#define FUEL_MAX 8
#define MINERAL_COLOR 1
#define MINERAL_CHAR 219
#define BG_STANDARD 0
#define FG_STANDARD 7
#define GROUND_RANDOM 20
#define GROUND_CHAR 177
#define BOX_WIDTH_MAX 30
#define BOX_HEIGHT_MAX 3

typedef struct{
    int32_t x,y;
    int8_t fuel;
    int8_t powerUp;
    int8_t shield;
} mineral_t;

typedef struct{
    int32_t x1,y1,x2, y2;
} boxes_t;

int8_t drawLandscape(int8_t change, int8_t colorBG, int8_t colorFG);


int randomNumber(int32_t mini, int32_t maxi);

void initMineral(mineral_t *p);
void drawMinerals(mineral_t minerals[], uint8_t numMinerals);
void createMineral(mineral_t minerals[], int8_t emptyIndex);
int8_t groundDraw(int8_t change, int8_t colorFG);

void initBoxes(boxes_t *box);
void createBoxes(boxes_t boxes[], int8_t emptyIndex);
void drawBoxes(boxes_t boxes[], int8_t numBoxes, int8_t colorFG);

void mineralKilled(mineral_t minerals[], int8_t index, int8_t numMinerals);

#endif
