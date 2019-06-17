#ifndef ALIENS_H
#define ALIENS_H

//#include "stm32f30x_rcc.h"
#include "ansi.h"
#include "30010_io.h"
#include "Landscape.h"

typedef struct {
    int posX, posY;
    int8_t alive;
    int8_t dir;
} alien_t;

void init_alien(alien_t *alien);
void updateAlien(alien_t *alien);
void updateAliens(alien_t aliens[], int8_t numAliens);
void alienKilled(alien_t *alien);
int8_t spawnAlien(alien_t aliens[], int8_t emptyIndex);


#endif

