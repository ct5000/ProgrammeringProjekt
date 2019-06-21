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
/*struct: bullet

    x and y represent the position of the bullet
    x: An integer that represents the bullets x position
    y: An integer that represents the bullets y position

    vx and vy represent the velocity of the bullet
    vx: an integer that represents the velocity across the x-axis
    vy: an integer that represents the velocity across the y-axis.

*/

typedef struct {
    int32_t x, y, vx, vy;
} cannonBall_t;



void initCannon(cannonBall_t *bullet, SpaceShip_t *ship);

void updateBallPosition(cannonBall_t *bullet);

int8_t inBallBounds(cannonBall_t *bullet);


int8_t readDegree();

int8_t hitAliens(alien_t aliens[], cannonBall_t bullets[], int8_t numAliens, int8_t numBalls);

void ballKilled(cannonBall_t cannonBalls[], int8_t index, int8_t numBalls);

void createBall(cannonBall_t cannonBalls[], int8_t emptyIndex, SpaceShip_t *ship);

void gravitate(cannonBall_t *p);


#endif



