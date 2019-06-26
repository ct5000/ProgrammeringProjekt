#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "mbed.h"
#include "ansi.h"
#include "Landscape.h"
#include "LCD.h"

#define START_LIVES 5
#define START_FUEL 20
#define START_Y 40
#define SPACESHIP_BORDER 2
#define MAX_FUEL 103
#define DRILL_CHAR 186
#define LCD_START_WRITE 30


/*  Struct: SpaceShip_t.
* -----------------------------------------------
* x; The spaceship's horizontal position.
* y; The spaceship's vertical position.
* vx; The spaceship's horizontal velocity.
* vy; The spaceship's vertical velocity.
* lives; The spaceship's lives.
* powerUp; the spaceship's power ups.
*/
typedef struct {
    int32_t x, y;
    int8_t vx, vy;
    int8_t lives;
    int16_t fuel;
    int8_t powerUp;
    int8_t shield;
} SpaceShip_t;

void initSpaceShip(SpaceShip_t *ball);
void shipNextLevel(SpaceShip_t *ship, uint8_t *buffer);
void updateSpaceShip(SpaceShip_t * ship, boxes_t boxes[]);
void updateVelocity(SpaceShip_t * ship, char key,  uint8_t *buffer, int place);
int8_t drill(SpaceShip_t * ship, char dirct, int8_t place, mineral_t minerals[], int numMinerals, uint8_t *buffer);

int8_t inBounds(SpaceShip_t *ship, boxes_t boxes[]);
int checkMinerals( SpaceShip_t *p, mineral_t minerals[],int numMinerals);

void addfuel(SpaceShip_t * ship, uint8_t *buffer);
void subfuel(SpaceShip_t * ship, uint8_t *buffer, int fuelSub);

void addLives(SpaceShip_t * ship, uint8_t *buffer);
void subLives(SpaceShip_t * ship, uint8_t *buffer);

int8_t endGameCondition(SpaceShip_t *ship, mineral_t minerals[], int numMinerals, int score);
int checkBoxes(int x, boxes_t boxes[], int numBoxes);

void addPowerBullet(SpaceShip_t * ship, uint8_t *buffer);
void subPowerBullet(SpaceShip_t * ship, uint8_t *buffer, int8_t usedPowerUp);

#endif

