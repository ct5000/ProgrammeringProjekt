#include "aliens.h"

void init_alien(alien_t *alien) {
    (*alien).alive = 1;
    (*alien).dir = 1; //1 means alien going right, 2 means alien going left
    (*alien).posX = 2;
    (*alien).posY = 2;
    drawAlien((*alien).posX, (*alien).posY);
}

void updateAlien(alien_t *alien) {
    deleteAlien((*alien).posX, (*alien).posY);
    if ((*alien).dir == 1) {
            if ((*alien).posX + 1 >= SCREEN_WIDTH) {
                    (*alien).dir = 2;
                    (*alien).posY += 3;
            }
            else {
                    (*alien).posX++;
            }
    }
    else {
            if ((*alien).posX - 1 <= 0) {
                    (*alien).dir = 1;
                    (*alien).posY += 3;
            }
            else {
                    (*alien).posX--;
            }
    }
    drawAlien((*alien).posX, (*alien).posY);
}



