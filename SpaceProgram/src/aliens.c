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
    (*alien).posX = randomNumber(ALIEN_BORDER,SCREEN_WIDTH-ALIEN_BORDER);
    (*alien).posY = ALIEN_Y;
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
    int num = randomNumber(0, DESCEND_CHANCE);
    deleteAlien((*alien).posX, (*alien).posY);

    if ((*alien).dir == 1) { //checks if the alien goes to the right
            if ((*alien).posX + ALIEN_BORDER >= SCREEN_WIDTH) { //checks if it hits the edge
                    (*alien).dir = 2;
            }
            else {
                    (*alien).posX++;
            }
    }
    else { //else alien is going left
            if ((*alien).posX - ALIEN_BORDER <= 0) { //checks if it hits the edge
                    (*alien).dir = 1;
            }
            else {
                    (*alien).posX--;
            }
    }
    if (num == 0) { //Check if alien goes down
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
        boxIndex = checkBoxes(aliens[i].posX, boxes, NUMBER_BOXES);
        if (boxIndex > 0){ //if the alien is above a box it is the box height to consider
            k = aliens[i].posY >= boxes[boxIndex-1].y2-ALIEN_BORDER;
        }
        else{
            k = aliens[i].posY >= GROUND_HEIGHT - ALIEN_BORDER;
        }
        if (k) { //checks if the alien is too low
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
    deleteAlien((aliens[index]).posX, (aliens[index]).posY);
    for (i = index; i < numAliens - 1; i ++) { //shifts aliens after the killed alien one to the left in the array
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
int8_t spawnAlien(alien_t aliens[], int8_t emptyIndex, int8_t spawnRate) {
    alien_t alien;
    int num = randomNumber(0, spawnRate);
    if (num == 0) { //creates alien if the random number is 0
            initAlien(&alien);
            aliens[emptyIndex] = alien;
            return 1;
    }
    return 0;
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
        for (j=0; j< numAliens; j++){ //runs through the aliens
            //get the data from alien and spaceship
            shipX = (*ship).x;
            aliX = aliens[j].posX;
            shipY = (*ship).y;
            aliY = aliens[j].posY;
            //checks for x and y direction
            inX= (shipX >= aliX - COLLISION_ZONE && shipX <= aliX + COLLISION_ZONE);
            inY= (shipY >= aliY - COLLISION_ZONE && shipY <= aliY + COLLISION_ZONE);
            if (inX && inY){ //checks if inside the box and damage the if it is
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
