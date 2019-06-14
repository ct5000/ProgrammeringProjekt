#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "vectors.h"
#include "serialRead.h"
#include "mbed.h"
#include "vectors.h"
#include "ansi.h"
#include "LUTsin.h"
#include "trigonometric.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t x, y;
} SpaceShip_t;

void initSpaceShip(SpaceShip_t *ball, int32_t x, int32_t y);
void updateSpaceShip(SpaceShip_t * ship, char dirct, int8_t place);
void drill(SpaceShip_t * ship, char dirct);


#endif

