#include "Cannon.h"


/* Function: initBullet
 * ---------------------------------
 * This function initializes the the position of a bullet to the spaceships position.
 * The velocity is set according to the potentiometer.
 *
 * bullet: A pointer to the bullet to be initialized
 * ship: A pointer to the spaceship that is flying around, thats position
 * will be used
 *
 * return: void
 */
void initBullet(bullet_t *bullet, SpaceShip_t *ship,int8_t isPower){
    (*bullet).x=(*ship).x <<FIX14_SHIFT;
    (*bullet).y=((*ship).y-2) <<FIX14_SHIFT;
    (*bullet).vx =  (-BULLET_SPEED * Cos(readDegree()));
    (*bullet).vy = (-BULLET_SPEED * Sin(readDegree()));
    (*bullet).powerUp= isPower;
}
/*
 * Function: updateBulletPosition
 * -----------------------------------
 * This function deletes the old symbol for the bullet. Determines the new position by adding the
 * velocity. If the bullet is in the legal area it is drawn. The velocity is also affected by gravity.
 *
 * bullet: A pointer to the bullet thats position is to be updated.
 *
 * return: void.
*/
int8_t updateBulletPosition(bullet_t *bullet, boxes_t boxes[]){
    int8_t bounds;
    char symbol = ((*bullet).powerUp) ? CHAR_POWERBULLET : CHAR_BULLET;
    deleteSymbol((*bullet).x>>FIX14_SHIFT, (*bullet).y>>FIX14_SHIFT);
    //update x- and y-coordinate for bullet
    (*bullet).x+=(*bullet).vx;
    (*bullet).y+=(*bullet).vy;
    bounds = inBulletBounds(bullet, boxes);
    gravitate(bullet);
    if (bounds){ //draw bullet if in bounds
        drawSymbol((*bullet).x>>14,(*bullet).y >>14, symbol);
    }
    else { //don't draw bullet but put x-coordinate back
        (*bullet).x-=(*bullet).vx;
    }
    return bounds;

}

/* Function: inBulletBounds
 * -------------------------------
 * This function determines determines if the bullet is above the ground but still
 * within the screen.
 * bullet: A pointer to the bullet that must be determined if is in the legal area.
 *
 * return: returns 1 if the bullet is in the legal area, otherwise 0.
 */

int8_t inBulletBounds(bullet_t *bullet, boxes_t boxes[]){
    int x = (*bullet).x >>FIX14_SHIFT;
    int y = (*bullet).y >>FIX14_SHIFT;
    int k = 0;

    int boxIndex = checkBoxes(x, boxes, NUMBER_BOXES);
    if (boxIndex > 0){ //checks if bullet is at box
           k = y < boxes[boxIndex-1].y2-BULLET_BORDER; //logic if the bullet is over box
    }
    else {
           k = y < GROUND_HEIGHT-BULLET_BORDER; //logic if the bullet is not over box
    }
    if ( x>=1 && x <=(SCREEN_WIDTH-BULLET_BORDER) && y >= BULLET_BORDER && k ){ //checks if the ball is in bounds
        return 1;
    }
    return 0;
}

/*Function: readDegree
 * --------------------------
 * This function interprets the input from the potentiometer as a degree between 0 and 180.
 *
 * Return: returns an integer between 0 and 180.
 */
int16_t readDegree(){
    return  (readPotRight()*100)/(2266);
}

/* Function: hitAliens
 * -----------------------------------
 * This function determines if any of the flying bullets have hit an alien, by having the
 * same position. A 2*2 box around the center of the alien is checked.
 *
 * aliens: An array of all the aliens.
 * bullet: An array of all the bullets.
 * numAliens: the number of flying aliens in the map.
 * numBullets: the number of flying bullets in the map
 *
 * return: An integer representing the number of aliens hit.
 *
 */
int8_t hitAliens(alien_t aliens[], bullet_t bullets[], int8_t numAliens, int8_t numBullets){
    int i,j;
    int inX,inY;
    int aliensHit = 0;
    int cannX;
    int aliX;
    int cannY;
    int aliY;

    for (i=0; i<numBullets; i++){ //runs through the bullets
        for (j=0; j< numAliens; j++){ //runs through the aliens
            //get the data from alien and bullet
            cannX = (bullets[i].x) >> FIX14_SHIFT;
            aliX = aliens[j].posX;
            cannY = (bullets[i].y) >> FIX14_SHIFT;
            aliY = aliens[j].posY;
            //checks for x and y direction
            inX= (cannX >= aliX - COLLISION_ZONE && cannX <= aliX + COLLISION_ZONE);
            inY= (cannY >= aliY - COLLISION_ZONE && cannY <= aliY + COLLISION_ZONE);
                if (inX && inY){ //checks if inside the box and kills the alien
                        alienKilled(aliens,j,numAliens);
                        aliensHit++;
                }
        }
    }
    return aliensHit;
}
/* Function: createBullet
 * ------------------------
 * This function adds initializes a new bullet to the list of active bullets.
 *
 * bullets: an array of all the bullets
 * emptyIndex: the index where the new bullet is to be placed
 * ship: a pointer to the active spaceship, which is used for the intialization
 *
 * return: void
 */
void createBullet(bullet_t bullets[], int8_t emptyIndex, SpaceShip_t *ship, int8_t type) {
    bullet_t bullet;
    initBullet(&bullet, ship,type);
    bullets[emptyIndex] = bullet;
}


/* Function: bulletKilled
 * -------------------------
 * This function updates the array of active bullets so the deceased bullet is not included.
 * This is either because it hit an alien or flew out of the map.
 *
 * bullets: An array of all the bullets
 * index: where in the array the newly deceased bullet is
 * numBullets: the number of active bullets in the map
 *
 * return: void
 *
 */
void bulletKilled(bullet_t bullets[], int8_t index, int8_t numBullets) {
    int8_t i;
    deleteSymbol( (((bullets[index]).x) >> FIX14_SHIFT) , (((bullets[index]).y) >> FIX14_SHIFT) );

    for (i = index; i < numBullets - 1; i++) {
        bullets[i] = bullets[i + 1];
    }
}


/* Function: gravitate
 * ------------------------
 * This function updates the velocity of the bullet as if it was affected by gravity,
 * depending on if it was fired straight up, to the left, or to the right of the spaceship.
 * This is determined using vx.
 *
 * bullet: A pointer to the bullets thats velocity must be updated.
 *
 * return: void.
 *
 */
void gravitate(bullet_t *bullet){
    int32_t tempx = (*bullet).vx;
    int8_t degree = 2;
    if ((*bullet).vx > 0){ //checks if bullet velocity is to the right
        //rotate the bullet with the clock
        (*bullet).vx = FIX14_MULT((*bullet).vx,Cos(degree)) - FIX14_MULT((*bullet).vy,Sin(degree));
        (*bullet).vy = FIX14_MULT(tempx,Sin(degree)) + FIX14_MULT((*bullet).vy,Cos(degree));
    }
    else if((*bullet).vx < 0){ //checks if bullet velocity is to the left
        //rotate the bullet against the clock
        degree *= -1;
        (*bullet).vx = FIX14_MULT((*bullet).vx,Cos(degree)) - FIX14_MULT((*bullet).vy,Sin(degree));
        (*bullet).vy = FIX14_MULT(tempx,Sin(degree)) + FIX14_MULT((*bullet).vy,Cos(degree));
    } else { //bullet velocity is straight up
        (*bullet).vy += degree <<6;
    }
}
