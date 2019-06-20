#include "Cannon.h"


void initCannon(cannonBall_t *p, SpaceShip_t *r){
    (*p).x=(*r).x <<14;
    (*p).y=((*r).y-2) <<14;

    (*p).vx =  (-2 * Cos(readDegree()));
    (*p).vy = (-2 * Sin(readDegree()));
}

void updateBallPosition(cannonBall_t *p){
    deleteSymbol((*p).x>>14, (*p).y>>14);

    (*p).x+=(*p).vx;
    (*p).y+=(*p).vy;

   gravitate(p);

    if (inBallBounds(p)){
        drawSymbol((*p).x>>14,(*p).y >>14, 169);
    }
}

int8_t inBallBounds(cannonBall_t *p){
    int x = (*p).x >>14;
    int y = (*p).y >>14;

    if (x>=1 && x <=238 && y >= 2 && y < GROUND_HEIGHT-1){
        return 1;
    }
    return 0;
}

int32_t readDegree(){
    return  (readPotRight()*100)/(2266);
}
int hitAliens(alien_t aliens[], cannonBall_t cannonballs[], int numAliens, int numBalls){
    int i,j;
    int inX,inY;
    int aliensHit = 0;
    int cannX;
    int aliX;
    int cannY;
    int aliY;

    for (i=0; i<numBalls; i++){
        for (j=0; j< numAliens; j++){
                        cannX = (cannonballs[i].x) >> 14;
            aliX = aliens[j].posX;
            cannY = (cannonballs[i].y) >> 14;
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
void createBall(cannonBall_t cannonBalls[], int8_t emptyIndex, SpaceShip_t *ship) {
    cannonBall_t cannonBall;

    initCannon(&cannonBall, ship);
    cannonBalls[emptyIndex] = cannonBall;
}

void ballKilled(cannonBall_t cannonBalls[], int8_t index, int8_t numBalls) {
    int i;
    deleteSymbol( (((cannonBalls[index]).x) >> 14) , (((cannonBalls[index]).y) >> 14) );
    for (i = index; i < numBalls - 1; i++) {
        cannonBalls[i] = cannonBalls[i + 1];
    }
}

void gravitate(cannonBall_t *p){
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




/*
Fra main


    uart_init(9600);
//    runningMenu();
    setup_pot();


    clrscr();
//    drawLandscape();
    int a=0;
    int p=-1;
    int i;
    int vinkel =0;
    cannonBall_t can;
    SpaceShip_t spac;


    initSpaceShip(&spac,20,20,100);

    cannonBall_t ammo[50];




    color(0,7);
    setup_pot();

    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;

    initSpaceShip(ship, 5, 5);



    while(1){

    char dirct = uart_get_char();
    updateSpaceShip(ship, dirct, inBounds(ship));
    drill(ship, dirct);


    while(1){
    if (uart_get_count() > 0) {

       if (uart_get_char()=='g'){
            p++;
            initCannon(&(ammo[p]), &spac);
       }
    }
    for (i=0; i<=p; i++){
        if (inBallBounds(&(ammo[p]))){
            updateBallPosition(&(ammo[p]));
        }
        else {
            deleteSymbol(&(ammo[p]).x,&(ammo[p]).y);
        }
    }

    }
*/



