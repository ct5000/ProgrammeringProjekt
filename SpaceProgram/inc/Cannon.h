

#ifndef CANNON_H
#define CANNON_H

#include "mbed.h"
#include "trigonometric.h"
#include <stdio.h>
#include <stdint.h>
#include "ansi.h"
#include "SpaceShip.h"
#include "vectors.h"
#include "aliens.h"


typedef struct {
    int32_t x, y, vx, vy;
} cannonBall_t;



void initCannon(char activate, cannonBall_t *p, SpaceShip_t *r);

void updateBallPosition(cannonBall_t *p);

int8_t inBallBounds(cannonBall_t *p);

void gravitate(cannonBall_t *p, int gravity);

void rotateDirection(cannonBall_t *p, int grader);

int32_t readDegree();

int* killAliens(alien_t aliens[], cannonBall_t cannonballs[]);

#endif



