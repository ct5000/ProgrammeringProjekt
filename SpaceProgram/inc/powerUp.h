#ifndef POWERUP_H
#define POWERUP_H

#include "mbed.h"
#include "trigonometric.h"
#include <stdio.h>
#include <stdint.h>
#include "ansi.h"
#include "SpaceShip.h"
#include "vectors.h"
#include "aliens.h"
#include "Cannon.h"


/*struct: bullet

    x and y represent the position of the power bullet
    x: An integer that represents the power bullets x position
    y: An integer that represents the power bullets y position

    vx and vy represent the velocity of the power bullet
    vx: an integer that represents the velocity across the x-axis
    vy: an integer that represents the velocity across the y-axis.

*/

typedef struct {
    int32_t x, y, vx, vy;
} powerBullet_t;



void initPowerBullet(powerBullet_t *p, SpaceShip_t *r);

void updatePowerBulletPosition(powerBullet_t *p); //bruges ikke

int powerHitAliens(alien_t aliens[], powerBullet_t powerBullets[], int numAliens, int numPowerBullets); //bruges ikke

int8_t inPowerBulletBounds(powerBullet_t *p);

void powerBulletKilled(powerBullet_t powerBullets[], int8_t index, int8_t numPowerBullets);

void createPowerBullet(powerBullet_t powerBullets[], int8_t emptyIndex, SpaceShip_t *ship);

void gravitatePowerBullet(powerBullet_t *pBullet);

void addPowerBullet(int numPowerBullets, uint8_t *buffer);

void subPowerBullet(SpaceShip_t * ship, uint8_t *buffer, int8_t usedPowerUp);


#endif

