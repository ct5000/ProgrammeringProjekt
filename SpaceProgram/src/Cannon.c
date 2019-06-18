#include "Cannon.h"


void initCannon(char activate, cannonBall_t *p, SpaceShip_t *r){
    if (activate=='g'){
        (*p).x=(*r).x <<14;
        (*p).y=((*r).y-1) <<14;

        (*p).vx =  2 * Cos(readDegree());
        (*p).vy = -2 * Sin(readDegree());
    }
}

void updateBallPosition(cannonBall_t *p){
    if (inBallBounds(p)){
        deleteSymbol((*p).x>>14, (*p).y>>14);

        (*p).x+=(*p).vx;
        (*p).y+=(*p).vy;

        drawSymbol((*p).x>>14,(*p).y >>14, 'O');
    }
    else {
        deleteSymbol((*p).x >>14, (*p).y>>14);
    }
}

int8_t inBallBounds(cannonBall_t *p){
    int x = (*p).x >>14;
    int y = (*p).y >>14;


    if (x>=1 && x <=238 && y >= 2){
        return 1;
    }
    return 0;
}

int32_t readDegree(){
    return  (readPotRight())/(22);
}
int* killAliens(alien_t aliens[], cannonBall_t cannonballs[]){
    int a = sizeof(aliens)/sizeof(aliens[0]);
    int c = sizeof(cannonballs)/sizeof(cannonballs[0]);
    int i,j;
    int inX,inY;
    int deadAliens[a];
    int p=0;

    for (i=0; i<c; i++){

        for (j=0; j<a; j++){
            inX=(cannonballs[i].x>=aliens[j].posX-1 && cannonballs[i].x<=aliens[j].posX+1);
            inY=(cannonballs[i].y>=aliens[j].posX-1 && cannonballs[i].y<=aliens[j].posY+1);
            if (inX && inY){
                    deleteAlien(aliens[j].posX,aliens[j].posY);
                    deadAliens[p]=j;
                    p++;
            }

    }
    return deadAliens;

}
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



