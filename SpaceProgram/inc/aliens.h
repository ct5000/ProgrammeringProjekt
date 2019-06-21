#ifndef ALIENS_H
#define ALIENS_H

#include "ansi.h"
#include "30010_io.h"
#include "Landscape.h"
#include "SpaceShip.h"


/*
 * Struct: alien_t
 * --------------------------
 * A struct to represent an alien
 *
 * posX: x-coordinate center position of the alien
 * posY: y-coordinate center position of the alien
 * dir: the direction the alien i moving. At 1 it moves right and at 2 it moves left
 *
 */
typedef struct {
    int posX, posY;
    int8_t dir;
} alien_t;

void init_alien(alien_t *alien);
void updateAlien(alien_t *alien);
void updateAliens(alien_t aliens[], SpaceShip_t * ship, int8_t numAliens, uint8_t *buffer);
void alienKilled(alien_t aliens[], int8_t index, int8_t numAliens);
int8_t spawnAlien(alien_t aliens[], int8_t emptyIndex, int spawnRate);
void makeAlien(alien_t aliens[], int8_t emptyIndex);
int8_t collide(alien_t aliens[], SpaceShip_t *ship, int8_t numAliens, uint8_t *buffer);


#endif

