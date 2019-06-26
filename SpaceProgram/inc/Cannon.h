#ifndef CANNON_H
#define CANNON_H

#include <stdio.h>
#include <stdint.h>

#include "mbed.h"
#include "trigonometric.h"
#include "ansi.h"
#include "SpaceShip.h"
#include "aliens.h"
#include "landscape.h"

#define CHAR_POWERBULLET 120
#define CHAR_BULLET 169
#define BULLET_SPEED 2
#define BULLET_BORDER 2


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
    int8_t powerUp;
} bullet_t;

void initCannon(bullet_t *bullet, SpaceShip_t *ship, int8_t isPower);
int8_t updateBulletPosition(bullet_t *bullet, boxes_t boxes[]);
int8_t inBulletBounds(bullet_t *bullet, boxes_t boxes[]);
int16_t readDegree();
int8_t hitAliens(alien_t aliens[], bullet_t bullets[], int8_t numAliens, int8_t numBullets);
void bulletKilled(bullet_t bullets[], int8_t index, int8_t numBullets);
void createBullet(bullet_t bullets[], int8_t emptyIndex, SpaceShip_t *ship, int8_t type);
void gravitate(bullet_t *p);

#endif
