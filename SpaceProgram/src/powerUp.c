#include "powerUp.h"

void initPowerBullet(powerBullet_t *p, SpaceShip_t *r) {
    (*p).x=(*r).x <<14;
    (*p).y=((*r).y-1) <<14;

    (*p).vx =  (-2 * Cos(readDegree()));
    (*p).vy = (-2 * Sin(readDegree()));
}

void updatePowerBulletPosition(powerBullet_t *p){
    deletePowerBullet((*p).x>>14, (*p).y>>14);

    (*p).x+=(*p).vx;
    (*p).y+=(*p).vy;

    gravitatePowerBullet(p);

    if (inPowerBulletBounds(p)){
        drawPowerBullet((*p).x>>14,(*p).y >>14);
    }
}

int8_t inPowerBulletBounds(powerBullet_t *p) {
    int x = (*p).x >>14;
    int y = (*p).y >>14;

    if (x>=1 && x <=238 && y >= 2 && y < GROUND_HEIGHT-1){
        return 1;
    }
    return 0;
}

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

void createPowerBullet(powerBullet_t powerBullets[], int8_t emptyIndex, SpaceShip_t *ship) {
    powerBullet_t powerBullet;

    initPowerBullet(&powerBullet, ship);
    powerBullets[emptyIndex] = powerBullet;
}

void powerBulletKilled(powerBullet_t powerBullets[], int8_t index, int8_t numPowerBullets) {
    int i;
    deletePowerBullet( (((powerBullets[index]).x) >> 14) , (((powerBullets[index]).y) >> 14) );
    for (i = index; i < numPowerBullets - 1; i ++) {
        powerBullets[i] = powerBullets[i + 1];
    }
}

void gravitatePowerBullet(powerBullet_t *p) {
    int32_t tempx = (*p).vx;
    int grader = 2;

    if ((*p).vx > 0){
    (*p).vx = FIX14_MULT((*p).vx,Cos(grader))-FIX14_MULT((*p).vy,Sin(grader));
    (*p).vy = FIX14_MULT(tempx,Sin(grader))+FIX14_MULT((*p).vy,Cos(grader));
    }
    else if(((*p).vx < 0)){
    grader *= -1;
    (*p).vx = FIX14_MULT((*p).vx,Cos(grader))-FIX14_MULT((*p).vy,Sin(grader));
    (*p).vy = FIX14_MULT(tempx,Sin(grader))+FIX14_MULT((*p).vy,Cos(grader));
    }
    else{
    (*p).vy += grader <<6;
    }

    //(*p).y = FIX14_MULT(tempx,Sin(grader))+FIX14_MULT((*p).y,Cos(grader));

}


