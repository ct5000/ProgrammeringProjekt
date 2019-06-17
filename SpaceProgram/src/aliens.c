#include "aliens.h"

void init_alien(alien_t *alien) {
    (*alien).alive = 1;
    (*alien).dir = 1; //1 means alien going right, 2 means alien going left
    (*alien).posX = 2;
    (*alien).posY = 5;
    drawAlien((*alien).posX, (*alien).posY);
}

void updateAlien(alien_t *alien) {
    deleteAlien((*alien).posX, (*alien).posY);
    if ((*alien).dir == 1) {
            if ((*alien).posX + 2 >= SCREEN_WIDTH) {
                    (*alien).dir = 2;
                    (*alien).posY += 3;
            }
            else {
                    (*alien).posX++;
            }
    }
    else {
            if ((*alien).posX - 2 <= 0) {
                    (*alien).dir = 1;
                    (*alien).posY += 3;
            }
            else {
                    (*alien).posX--;
            }
    }
    drawAlien((*alien).posX, (*alien).posY);
}

void updateAliens(alien_t aliens[], int8_t numAliens) {
    int i;
    while ((aliens[0]).alive == 0) {
            aliens++;
            aliens = realloc(aliens, 20 * sizeof (alien_t));
    }

    for (i = 0; i < numAliens; i++) {
            if ((aliens[i]).alive) {
                updateAlien(&aliens[i]);
            }
    }
}

void alienKilled(alien_t *alien) {
    (*alien).alive = 0;
    deleteAlien((*alien).posX, (*alien).posY);
}

int8_t spawnAlien(alien_t aliens[], int8_t emptyIndex) {
    alien_t alien;
    int num = randomNumber(0, 100);
    if (num == 50) {
            init_alien(&alien);
            aliens[emptyIndex] = alien;
            return 1;
    }
    return 0;
}


