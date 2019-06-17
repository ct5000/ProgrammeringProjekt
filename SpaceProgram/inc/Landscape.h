#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ansi.h"
//#include "SpaceShip.h"

# define SCREEN_WIDTH 192
# define SCREEN_HEIGHT 55
# define GROUND_HEIGHT 40

typedef struct{
    int8_t x,y;
    int8_t fuel;
} mineral_t;

void drawLandscape();

int randomNumber(int8_t mini, int8_t maxi);
void initMineral(mineral_t *p);
void drawMinerals(mineral_t minerals[]);

#endif
