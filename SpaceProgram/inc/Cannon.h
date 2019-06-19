

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



void initCannon(cannonBall_t *p, SpaceShip_t *r);

void updateBallPosition(cannonBall_t *p);

int8_t inBallBounds(cannonBall_t *p);

void rotateDirection(cannonBall_t *p, int grader);

int32_t readDegree();

int hitAliens(alien_t aliens[], cannonBall_t cannonballs[], int numAliens, int numBalls);

void ballKilled(cannonBall_t cannonBalls[], int8_t index, int8_t numBalls);

void createBall(cannonBall_t cannonBalls[], int8_t emptyIndex, SpaceShip_t *ship);

void gravitate(cannonBall_t *p);


#endif



