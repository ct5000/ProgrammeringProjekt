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
//#include "aliens.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int32_t x, y;
    int8_t vx, vy;
    int8_t lives;
    int16_t fuel;
    int8_t powerUp;
} SpaceShip_t;

void initSpaceShip(SpaceShip_t *ball, int32_t x, int32_t y, int16_t fuel);
void updateSpaceShip(SpaceShip_t * ship);
void updateVelocity(SpaceShip_t * ship, char dirct,  uint8_t *buffer, int place);
int8_t drill(SpaceShip_t * ship, char dirct, int8_t place, mineral_t minerals[], int numMinerals, uint8_t *buffer);
void mineralKilled(mineral_t minerals[], int8_t index, int8_t numMinerals);

int8_t inBounds(SpaceShip_t *p);
int checkMinerals( SpaceShip_t *p, mineral_t minerals[],int numMinerals);

void addfuel(SpaceShip_t * ship, uint8_t *buffer);
void subfuel(SpaceShip_t * ship, uint8_t *buffer, int fuelSub);

void addLives(SpaceShip_t * ship, uint8_t *buffer);
void subLives(SpaceShip_t * ship, uint8_t *buffer);

int8_t endGameCondition(SpaceShip_t *ship, mineral_t minerals[], int numMinerals, int score);


#endif

