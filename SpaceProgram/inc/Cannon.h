#include "mbed.h"
#include "trigonometric.h"
#include <stdio.h>
#include <stdint.h>
#include "ansi.h"
#include "SpaceShip.h"
#include "vectors.h"

#ifndef CANNON_H
#define CANNON_H

typedef struct {
    int32_t x, y, vx, vy;


} cannonBall_t;



void initCannon(cannonBall_t *p, SpaceShip_t *r);

void updateBallPosition(cannonBall_t *p);

int8_t inBallBounds(cannonBall_t *p);

void gravitate(cannonBall_t *p, int gravity);

void rotateDirection(cannonBall_t *p, int grader);

int32_t readDegree();

#endif



