#include "aliens.h"

/*
 * Function: initAlien
 * --------------------------
 * Initializes an alien with a random direction, a random y-coordinate, and at the top of the screen.
 * It also draws the alien
 *
 * alien: the alien that needs to be initialized.
 *
 * returns: void
 */
void initAlien(alien_t *alien) {
    (*alien).dir = randomNumber(1, 2); //1 means alien going right, 2 means alien going left
    (*alien).posX = randomNumber(3,SCREEN_WIDTH-3);
    (*alien).posY = 3;
    drawAlien((*alien).posX, (*alien).posY);
}

/*
 * Function: updateAlien
 * --------------------------
 * Updates the position of the alien and moves the graphic. If hit hits the sides the alien turns around.
 * The alien jumps down at a random moment.
 *
 * alien: the alien that needs to be updated
 *
 * returns: void
 */
void updateAlien(alien_t *alien) {
    int num = randomNumber(0, 15);
    deleteAlien((*alien).posX, (*alien).posY);

    if ((*alien).dir == 1) {
            if ((*alien).posX + 2 >= SCREEN_WIDTH) {
                    (*alien).dir = 2;
            }
            else {
                    (*alien).posX++;
            }
    }
    else {
            if ((*alien).posX - 2 <= 0) {
                    (*alien).dir = 1;
            }
            else {
                    (*alien).posX--;
            }
    }
    if (num == 0) {
            (*alien).posY += 3;
    }

    drawAlien((*alien).posX, (*alien).posY);
}

/*
 * Function: updateAliens
 * --------------------------
 * Updates the position of all the aliens in an array and checks whether it gets to ground height, and it damages the player accordingly.
 *
 * aliens: the array of aliens to be updated.
 * ship: the ship that can be damaged by the aliens.
 * numAliens: the number of aliens in the array.
 * buffer: an array for the lights on the LCD display
 *
 * returns: void
 */
void updateAliens(alien_t aliens[],SpaceShip_t * ship , int8_t numAliens, uint8_t *buffer, boxes_t boxes[]) {
    int i;
    int boxIndex;
    int k;

    for (i = 0; i < numAliens; i++) {
            updateAlien(&aliens[i]);
            boxIndex = checkBoxes(aliens[i].posX, boxes, 10);
            if (boxIndex > 0){
                k = aliens[i].posY >= boxes[boxIndex-1].y2-3;
            }
            else{
                k = aliens[i].posY >= GROUND_HEIGHT - 3;
            }
            if (k) {
                alienKilled(aliens, i, numAliens);

                if ((*ship).shield == 1){
                    (*ship).shield = 0;
                }
                else{
                    subLives(ship,buffer);
                }
            }
    }
}

/*
 * Function: alienKilled
 * --------------------------
 * Kills an alien and shifts the positions of the remaining aliens one to the left
 *
 * aliens: the array of aliens where an alien has been killed.
 * index: the index of the killed alien
 * numAliens: the number of aliens in the array including the killed alien.
 *
 * returns: void
 */
void alienKilled(alien_t aliens[], int8_t index, int8_t numAliens) {
    int i;
    //(*alien).alive = 0;
    deleteAlien((aliens[index]).posX, (aliens[index]).posY);
    for (i = index; i < numAliens - 1; i ++) {
        aliens[i] = aliens[i + 1];
    }

}

/*
 * Function: spawnAlien
 * --------------------------
 * Spawns an alien in an array with a chance depending on the spawn rate.
 *
 * aliens: the array of aliens where an alien might be spawned.
 * emptyIndex: the index where an alien can be spawned
 * spawnRate: the chance that an alien can be spawned.
 *
 * returns: An 1 if there has been spawned an alien or else an 0.
 */
int8_t spawnAlien(alien_t aliens[], int8_t emptyIndex, int spawnRate) {
    alien_t alien;
    int num = randomNumber(0, spawnRate);
    if (num == 0) {
            initAlien(&alien);
            aliens[emptyIndex] = alien;
            return 1;
    }
    return 0;
}

/*
 * Function: makeAlien
 * --------------------------
 * Makes an alien in an array
 *
 * aliens: the array of aliens where an alien should be made.
 * emptyIndex: the index where an alien can be spawned
 *
 * returns: void
 */
void makeAlien(alien_t aliens[], int8_t emptyIndex) {
    alien_t alien;
    initAlien(&alien);
    aliens[emptyIndex] = alien;
}

/*
 * Function: collide
 * --------------------------
 * Checks through an array of aliens whether they hit a spaceship. If an alien hits it dies
 *
 * aliens: the array of aliens where an alien might hit the spaceship.
 * ship: the ship that might be hit by aliens.
 * numAliens: the number of aliens in the array
 * buffer: an array for the lights on the LCD display
 *
 * returns: the number of aliens that hit the spaceship
 */
int8_t collide(alien_t aliens[], SpaceShip_t *ship, int8_t numAliens, uint8_t *buffer){
    int j;
    int inX,inY;
    int shipX, aliX, shipY, aliY;
    int aliensHit = 0;
        for (j=0; j< numAliens; j++){
            shipX = (*ship).x;
            aliX = aliens[j].posX;
            shipY = (*ship).y;
            aliY = aliens[j].posY;
            inX= (shipX >= aliX - 2 && shipX <= aliX + 2);
            inY= (shipY >= aliY - 2 && shipY <= aliY + 2);
            if (inX && inY){
                    if( (*ship).shield == 1){
                        (*ship).shield = 0;
                    }
                    else{
                    subLives(ship, buffer);
                    }
                    alienKilled(aliens,j,numAliens);
                    aliensHit++;
            }
        }
    return aliensHit;
}
