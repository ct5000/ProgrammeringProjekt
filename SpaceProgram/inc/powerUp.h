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


typedef struct {
    int32_t x, y, vx, vy;
} powerBullet_t;



void initPowerBullet(powerBullet_t *p, SpaceShip_t *r);

void updatePowerBulletPosition(powerBullet_t *p);

int powerHitAliens(alien_t aliens[], powerBullet_t powerBullets[], int numAliens, int numPowerBullets);

int8_t inPowerBulletBounds(powerBullet_t *p);

void powerBulletKilled(powerBullet_t powerBullets[], int8_t index, int8_t numPowerBullets);

void createPowerBullet(powerBullet_t powerBullets[], int8_t emptyIndex, SpaceShip_t *ship);

void gravitatePowerBullet(powerBullet_t *p);

void addPowerBullet(int numPowerBullets, uint8_t *buffer);

void subPowerBullet(SpaceShip_t * ship, uint8_t *buffer);


#endif

