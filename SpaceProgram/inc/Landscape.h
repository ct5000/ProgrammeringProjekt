#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ansi.h"
//#include "SpaceShip.h"

# define SCREEN_WIDTH 240
# define SCREEN_HEIGHT 76
# define GROUND_HEIGHT 56

typedef struct{
    int32_t x,y;
    int8_t fuel;
    int8_t powerUp;
} mineral_t;

void drawLandscape();

int randomNumber(int32_t mini, int32_t maxi);
void initMineral(mineral_t *p);
void drawMinerals(mineral_t minerals[], int numMinerals);
int8_t createMineral(mineral_t minerals[], int8_t emptyIndex);
void groundDraw();

#endif
