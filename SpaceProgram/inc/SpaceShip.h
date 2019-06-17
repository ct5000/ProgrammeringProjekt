#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "vectors.h"
#include "serialRead.h"
#include "mbed.h"
#include "vectors.h"
#include "ansi.h"
#include "LUTsin.h"
#include "trigonometric.h"
#include "Landscape.h"
#include "LCD.h"
#include "aliens.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int32_t x, y;
    int8_t fuel;
} SpaceShip_t;

void initSpaceShip(SpaceShip_t *ball, int32_t x, int32_t y, int16_t fuel);
void updateSpaceShip(SpaceShip_t * ship, char dirct, int8_t place);
void drill(SpaceShip_t * ship, char dirct, int8_t place, mineral_t minerals[]);

int8_t inBounds(SpaceShip_t *p);
int checkMinerals( SpaceShip_t *p, mineral_t minerals[]);

void addfuel(SpaceShip_t * ship);
void subfuel(SpaceShip_t * ship);



#endif

