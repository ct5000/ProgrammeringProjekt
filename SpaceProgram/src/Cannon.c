#include "Cannon.h"

/*
Function: initBullet
This function intializes the the position of a bullet to the spaceships position.
The velocity is set according to the potentiometer.
bullet: A pointer to the bullet to be intialized
ship: A pointer to the spaceship that is flying around, thats position
will be used

return: void
*/
void initCannon(cannonBall_t *bullet, SpaceShip_t *ship){
    (*bullet).x=(*ship).x <<14;
    (*bullet).y=((*ship).y-1) <<14;

    (*bullet).vx =  (-2 * Cos(readDegree()));
    (*bullet).vy = (-2 * Sin(readDegree()));
}
/*
Function: updateBulletPosition
This function deletes the old symbol for the bullet. Determines the new position by adding the
velocity. If the bullet is in the legal area it is drawn. The velocity is also affected by gravity.

bullet: A pointer to the bullet thats position is to be updated.

return: void.

*/
void updateBallPosition(cannonBall_t *bullet){
    deleteSymbol((*bullet).x>>14, (*bullet).y>>14);

    (*bullet).x+=(*bullet).vx;
    (*bullet).y+=(*bullet).vy;

    gravitate(bullet);

    if (inBallBounds(bullet)){
        drawSymbol((*bullet).x>>14,(*bullet).y >>14, 169);
    }
}
/* Function: inBulletBounds
This function determines determines if the bullet is above the ground but still
within the screen.
bullet: A pointer to the bullet that must be determined if is in the legal area.

return: returns 1 if the bullet is in the legal area, otherwise 0.
*/

int8_t inBallBounds(cannonBall_t *bullet){
    int x = (*bullet).x >>14;
    int y = (*bullet).y >>14;

    if (x>=1 && x <=(SCREEN_WIDTH-2) && y >= 2 && y < GROUND_HEIGHT-1){
        return 1;
    }
    return 0;
}

/*Function: readDegree
This function interprets the input from the potentiometer as a degree between 0 and 180.
Return: returns an integer between 0 and 180.
*/


int8_t readDegree(){
    return  (readPotRight()*100)/(2266);
}

/*Function: hitAliens
This function determines if any of the flying bullets have hit an alien, by having the
same position. A 2*2 box around the center of the alien is checked.

aliens: An array of all the aliens.
bullet: An array of all the bullets.
numAliens: the number of flying aliens in the map.
numBullets: the number of flying bullets in the map

return: An integer representing the number of aliens hit.

*/
int8_t hitAliens(alien_t aliens[], cannonBall_t bullets[], int8_t numAliens, int8_t numBullets){
    int i,j;
    int inX,inY;
    int aliensHit = 0;
    int cannX;
    int aliX;
    int cannY;
    int aliY;

    for (i=0; i<numBullets; i++){
        for (j=0; j< numAliens; j++){
            cannX = (bullets[i].x) >> 14;
            aliX = aliens[j].posX;
            cannY = (bullets[i].y) >> 14;
            aliY = aliens[j].posY;

            inX= (cannX >= aliX - 2 && cannX <= aliX + 2);
            inY= (cannY >= aliY - 2 && cannY <= aliY + 2);

                if (inX && inY){
                        alienKilled(aliens,j,numAliens);
                        aliensHit++;
                }
        }
    }
    return aliensHit;
}
/*Function: createBullet
This function adds intializes a new bullet to the list of active bullets.

bullets: an array of all the active bullets
emptyIndex: the index where the new bullet is to be placed
ship: a pointer to the active spaceship, which is used for the intialization

return: void
*/
void createBall(cannonBall_t bullets[], int8_t emptyIndex, SpaceShip_t *ship) {
    cannonBall_t bullet;

    initCannon(&bullet, ship);
    bullets[emptyIndex] = bullet;
}

/*Function: bulletKilled
This function updates the array of active bullets so the deceased bullet is not included.
This is either because it hit an alien or flew out of the map.

bullets: An array of all the bullets
index: where in the array the newly deceased bullet is
numBullets: the number of active bullets in the map

return: void

*/
void ballKilled(cannonBall_t bullets[], int8_t index, int8_t numBullets) {
    int8_t i;
    deleteSymbol( (((bullets[index]).x) >> 14) , (((bullets[index]).y) >> 14) );

    for (i = index; i < numBullets - 1; i++) {
        bullets[i] = bullets[i + 1];
    }
}
/*Function: gravitate
This function updates the velocity of the bullet as if it was affected by gravity,
depending on if it was fired straight up, to the left, or to the right of the spaceship.
This is determined using vx.

bullet: A pointer to the bullets thats velocity must be updated.

return: void.

*/


void gravitate(cannonBall_t *bullet){
    int32_t tempx = (*bullet).vx;
    int8_t degree = 2;

    if ((*bullet).vx > 0){
        //FIX14_MULT is used to multiply numbers that are shifted 14
        (*bullet).vx = FIX14_MULT((*bullet).vx,Cos(degree)) - FIX14_MULT((*bullet).vy,Sin(degree));
        (*bullet).vy = FIX14_MULT(tempx,Sin(degree)) + FIX14_MULT((*bullet).vy,Cos(degree));
    }
    else if((*bullet).vx < 0){
        degree *= -1;
        (*bullet).vx = FIX14_MULT((*bullet).vx,Cos(degree)) - FIX14_MULT((*bullet).vy,Sin(degree));
        (*bullet).vy = FIX14_MULT(tempx,Sin(degree)) + FIX14_MULT((*bullet).vy,Cos(degree));
    }
    else{
        (*bullet).vy += degree <<6;
    }


}
