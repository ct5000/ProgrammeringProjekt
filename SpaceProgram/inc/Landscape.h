#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ansi.h"
//#include "SpaceShip.h"

# define SCREEN_WIDTH 240
# define SCREEN_HEIGHT 66
# define GROUND_HEIGHT 56

typedef struct{
    int32_t x,y;
    int8_t fuel;
    int8_t powerUp;
} mineral_t;

typedef struct{
    int32_t x1,y1,x2, y2;
} boxes_t;

void drawLandscape();


int randomNumber(int32_t mini, int32_t maxi);
void initMineral(mineral_t *p);
void drawMinerals(mineral_t minerals[], int numMinerals);
void createMineral(mineral_t minerals[], int8_t emptyIndex);
int8_t groundDraw();

void initBoxes(boxes_t *box);
void createBoxes(boxes_t boxes[], int8_t emptyIndex);
void drawBoxes(boxes_t boxes[], int numBoxes);

void mineralKilled(mineral_t minerals[], int8_t index, int8_t numMinerals);

#endif
