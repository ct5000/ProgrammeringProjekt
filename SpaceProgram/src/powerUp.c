#include "powerUp.h"

/*
Function: initPowerBullet
This function initializes the position of a power bullet to the spaceships position.
The velocity is set according to the potentiometer.
pBullet: A pointer to the power bullet to be intialized
ship: A pointer to the spaceship that is flying around, thats position
will be used

return: void
*/

void initPowerBullet(powerBullet_t *pBullet, SpaceShip_t *ship) {
    (*pBullet).x=(*ship).x <<14;
    //the y coordinate is higher since the character for the Pbullet fills two spaces
    (*pBullet).y=((*ship).y-3) <<14;

    (*pBullet).vx =  (-2 * Cos(readDegree()));
    (*pBullet).vy = (-2 * Sin(readDegree()));
}

/*
Function: updatePowerBulletPosition
This function deletes the old symbol for the power bullet. Determines the new position by adding the
velocity. If the  power bullet is in the legal area it is drawn. The velocity is also affected by gravity.

pBullet: A pointer to the power bullet thats position is to be updated.

return: void.

*/
void updatePowerBulletPosition(powerBullet_t *pBullet){
    deletePowerBullet((*pBullet).x>>14, (*pBullet).y>>14);

    (*pBullet).x+=(*pBullet).vx;
    (*pBullet).y+=(*pBullet).vy;

    gravitatePowerBullet(pBullet);

    if (inPowerBulletBounds(pBullet)){
        drawPowerBullet((*pBullet).x>>14,(*pBullet).y >>14);
    }
}
/* Function: inPowerBulletBounds
This function determines determines if the power bullet is above the ground but still
within the screen.
pBullet: A pointer to the power bullet that must be determined if is in the legal area.

return: returns 1 if the bullet is in the legal area, otherwise 0.
*/

int8_t inPowerBulletBounds(powerBullet_t *pBullet) {
    int x = (*pBullet).x >>14;
    int y = (*pBullet).y >>14;

    if (x>=1 && x <=238 && y >= 2 && y < GROUND_HEIGHT-2){
        return 1;
    }
    return 0;
}

/*Function: powerHitAliens
This function determines if any of the flying power bullets have hit an alien, by having the
same position. A 3*3 box around the center of the alien is checked.

aliens: An array of all the aliens.
bullet: An array of all the bullets.
numAliens: the number of flying aliens in the map.
numPowerBullets: the number of flying power bullets in the map

return: An integer representing the number of aliens hit.

*/

int powerHitAliens(alien_t aliens[], powerBullet_t powerBullets[], int numAliens, int numPowerBullets){
    int i,j;
    int inX,inY;
    int aliensHit = 0;
    int cannX;
    int aliX;
    int cannY;
    int aliY;

    for (i=0; i< numPowerBullets; i++){
        for (j=0; j< numAliens; j++){
            cannX = (powerBullets[i].x) >> 14;
            aliX = aliens[j].posX;
            cannY = (powerBullets[i].y) >> 14;
            aliY = aliens[j].posY;

            inX= (cannX + 1 >= aliX - 2 && cannX <= aliX + 2);
            inY= (cannY + 1 >= aliY - 2 && cannY <= aliY + 2);
            if (inX && inY){
                    alienKilled(aliens,j,numAliens);
                    aliensHit++;
            }
        }
    }
    return aliensHit;
}

/*Function: createBullet
This function adds intializes a new power bullet to the list of active power bullets.

bullets: an array of all the bullets
emptyIndex: the index where the new bullet is to be placed
ship: a pointer to the active spaceship, which is used for the intialization

return: void
*/

void createPowerBullet(powerBullet_t powerBullets[], int8_t emptyIndex, SpaceShip_t *ship) {
    powerBullet_t powerBullet;

    initPowerBullet(&powerBullet, ship);
    powerBullets[emptyIndex] = powerBullet;
}

/*Function: bulletKilled
This function updates the array of active bullets so the deceased bullet is not included.
This is either because it hit an alien or flew out of the map.

bullets: An array of all the bullets
index: where in the array the newly deceased bullet is
numBullets: the number of active bullets in the map

return: void

*/

void powerBulletKilled(powerBullet_t powerBullets[], int8_t index, int8_t numPowerBullets) {
    int i;
    deletePowerBullet( (((powerBullets[index]).x) >> 14) , (((powerBullets[index]).y) >> 14) );
    for (i = index; i < numPowerBullets - 1; i++) {
        powerBullets[i] = powerBullets[i + 1];
    }
}
/*Function: gravitate
This function updates the velocity of the bullet as if it was affected by gravity,
depending on if it was fired straight up, to the left, or to the right of the spaceship.
This is determined using vx.

bullet: A pointer to the power bullet thats velocity must be updated.

return: void.

*/



void gravitatePowerBullet(powerBullet_t *p) {
    int32_t tempx = (*pBullet).vx;
    int grader = 2;

    if ((*pBullet).vx > 0){
        (*pBullet).vx = FIX14_MULT((*pBullet).vx,Cos(grader))-FIX14_MULT((*pBullet).vy,Sin(grader));
        (*pBullet).vy = FIX14_MULT(tempx,Sin(grader))+FIX14_MULT((*pBullet).vy,Cos(grader));
    }
    else if(((*pBullet).vx < 0)){
        grader *= -1;
        (*pBullet).vx = FIX14_MULT((*pBullet).vx,Cos(grader))-FIX14_MULT((*pBullet).vy,Sin(grader));
        (*pBullet).vy = FIX14_MULT(tempx,Sin(grader))+FIX14_MULT((*pBullet).vy,Cos(grader));
    } else {
        (*pBullet).vy += grader <<6;
    }
}

/*Function: addPowerBullet
This function is used update the LCD display when a new power bullet is found.
An 'O' is added for every powerBullet on line 3.

numPowerBullets: the total number of power bullets
buffer: an 512 long array where every element represents a character on LCD display

return void

*/

void addPowerBullet(int numPowerBullets, uint8_t *buffer){
    int i;

        for(i=0; i < numPowerBullets; i++){

        lcd_write_string("O", buffer, 2,30+i*5);

        lcd_push_buffer(buffer);
        }
}

/*Function: subPowerBullet
Keeps the amount of power bullets updated when one is used.
The LCD display is updated to show the correct number of power bullets.

ship: a pointer to the active spaceship. It is used to get the number of power ups.
buffer: an 512 long array where every element represents a character on LCD display

return:void
*/
void subPowerBullet(SpaceShip_t * ship, uint8_t *buffer){
        int8_t i;
        //the number of powerups is copied as not to update the stopcondition while the
        //loop is running
        int copyPowerUp = (*ship).powerUp;
        for (i=0; i<copyPowerUp; i++){
            (*ship).powerUp--;
            lcd_write_string(" ", buffer, 2,30+(*ship).powerUp*5);
            lcd_push_buffer(buffer);
        }

}


