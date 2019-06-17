#include "Cannon.h"


void initCannon(cannonBall_t *p, SpaceShip_t *r){
    (*p).x=(*r).x <<14;
    (*p).y=((*r).y-1) <<14;

    (*p).vx =  2 * Cos(readDegree());
    (*p).vy = -2 * Sin(readDegree());

}

void updateBallPosition(cannonBall_t *p){
    deleteSymbol((*p).x>>14, (*p).y>>14);

    (*p).x+=(*p).vx;
    (*p).y+=(*p).vy;

    drawSymbol((*p).x>>14,(*p).y >>14, 'O');

}

int8_t inBallBounds(cannonBall_t *p){
    int x = (*p).x >>14;
    int y = (*p).y >>14;


    if (x>=0 && x <=240 && y >= 0){
        return 1;
    }
    return 0;
}


void gravitate(cannonBall_t *p, int gravity){

//    switch(gravity){
//        case 1:
//            rotateDirection(p, 30);
//            break;
//        case 2:
//            rotateDirection(p, 45);
//            break;
//        case 3:
//            rotateDirection(p, 60);
//            break;
//    }

}

void rotateDirection(cannonBall_t *p, int grader){
//    int32_t tempx = (*p).x;
//    (*p).x = FIX14_MULT((*p).x,Cos(grader))-FIX14_MULT((*p).y,Sin(grader));
//    (*p).y = FIX14_MULT(tempx,(-1)*Sin(grader))+FIX14_MULT((*p).y,Cos(grader));
}


int32_t readDegree(){
    return  (readPotRight())/(22);
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



