#include "aliens.h"

void init_alien(alien_t *alien) {
    (*alien).dir = 1; //1 means alien going right, 2 means alien going left
    (*alien).posX = 2;
    (*alien).posY = 5;
    drawAlien((*alien).posX, (*alien).posY);
}

void updateAlien(alien_t *alien) {
    deleteAlien((*alien).posX, (*alien).posY);
    if ((*alien).dir == 1) {
            if ((*alien).posX + 2 >= SCREEN_WIDTH) {
                    (*alien).dir = 2;
                    (*alien).posY += 3;
            }
            else {
                    (*alien).posX++;
            }
    }
    else {
            if ((*alien).posX - 2 <= 0) {
                    (*alien).dir = 1;
                    (*alien).posY += 3;
            }
            else {
                    (*alien).posX--;
            }
    }
    drawAlien((*alien).posX, (*alien).posY);
}

void updateAliens(alien_t aliens[],SpaceShip_t * ship , int8_t numAliens, uint8_t *buffer) {
    int i;
    for (i = 0; i < numAliens; i++) {
            updateAlien(&aliens[i]);
            if (aliens[i].posY >= GROUND_HEIGHT - 3) {
                alienKilled(aliens, i, numAliens);
                subLives(ship,buffer);
            }
    }
}

void alienKilled(alien_t aliens[], int8_t index, int8_t numAliens) {
    int i;
    //(*alien).alive = 0;
    deleteAlien((aliens[index]).posX, (aliens[index]).posY);
    for (i = index; i < numAliens - 1; i ++) {
        aliens[i] = aliens[i + 1];
    }

}

int8_t spawnAlien(alien_t aliens[], int8_t emptyIndex, int spawnRate) {
    alien_t alien;
    int num = randomNumber(0, spawnRate);
    if (num == 0) {
            //aliens = realloc(aliens, (emptyIndex + 1) * sizeof(alien_t));
            init_alien(&alien);
            aliens[emptyIndex] = alien;
            return 1;
    }
    return 0;
}

void makeAlien(alien_t aliens[], int8_t emptyIndex) {
    alien_t alien;
    //aliens = realloc(aliens, (emptyIndex + 1) * sizeof(alien_t));
    init_alien(&alien);
    aliens[emptyIndex] = alien;
}

int8_t collide(alien_t aliens[], SpaceShip_t *ship, int numAliens, uint8_t *buffer){
    int j;
    int inX,inY;
    int shipX;
    int aliX;
    int shipY;
    int aliY;
    int aliensHit = 0;


        for (j=0; j< numAliens; j++){
            shipX = (*ship).x;
            aliX = aliens[j].posX;
            shipY = (*ship).y;
            aliY = aliens[j].posY;

            inX= (shipX >= aliX - 2 && shipX <= aliX + 2);
            inY= (shipY >= aliY - 2 && shipY <= aliY + 2);
            if (inX && inY){
                    subLives(ship, buffer);
                    alienKilled(aliens,j,numAliens);
                    aliensHit++;


            }
        }
    return aliensHit;
}



/*
Kode fra main


    alien_t aliens[25];
    int8_t numAliens = 0;
    int8_t noYet = 1;
    uart_init(96000);
    //runningMenu();
    set_timer();

    clrscr();
    drawLandscape();



    bgcolor(6);
    //setup_pot();

    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;

    initSpaceShip(ship, 5, 5, 100);

    drawfuelBar(ship);
    makeAlien(aliens, numAliens);
    numAliens++;
    start_stop();







    while(1){

            if(spawnAlien(aliens, numAliens)) {
                    numAliens++;
            }
            if (getFlag() > 15000 && noYet) {
                    alienKilled(aliens, 1, numAliens);
                    numAliens--;
                    noYet = 0;
            }
            updateAliens(aliens, numAliens);
            char dirct = uart_get_char();
            updateSpaceShip(ship, dirct, inBounds(ship));
            drill(ship, dirct,inBounds(ship));

            usefuelBar(ship, dirct);

    }

*/
