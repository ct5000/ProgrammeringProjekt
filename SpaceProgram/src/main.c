/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h" //STM32 config
#include "30010_io.h" // Input/output libarary for this course
#include "ansi.h"
#include "LUTsin.h"
#include "trigonometric.h"
#include "vectors.h"
#include "ball.h"
#include "mbed.h"
#include "serialRead.h"
#include "LCD.h"
#include "charset.h"
#include "SpaceShip.h"
#include "Landscape.h"
#include "menu.h"
#include "aliens.h"
#include "Cannon.h"
#include "powerUp.h"
#include "bossKey.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ESC 0x1B





int main(void){
    alien_t aliens[25];
    int8_t numAliens = 0;
    int8_t killedAliens;

    mineral_t minerals[25];
    int8_t numMinerals = 0;
    int8_t mineralIndex;

    cannonBall_t cannonBalls[50];
    int8_t numBalls = 0;

    powerBullet_t powerBullets[5];
    int8_t numPowerBullets = 0;

    int i;
    int endgame = 0;
    int where = 1;
    int oldWhere = 1;
    char dirct;

    int spawnRate = 50;

    int score = 1000;

    int pos;
    //int readyDirct = 1;


    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;


    uint8_t buffer[512];

    uart_init(960000);

    set_timer();
    start_stop();
    lcd_init();
    memset(buffer, 0x00, 512);
    lcd_push_buffer(buffer);
    lcd_write_string("FUEL:",buffer,0,0);
    lcd_write_string("Lives:",buffer,1,0);
    lcd_push_buffer(buffer);

    setup_pot();

    color(7,0);

    while(1){
        switch(where){
            case 1:
                spawnRate = 50;
                runningMenu();
                srand(getTime());
                resetTime();
                start_stop();

                clrscr();

                drawLandscape();
                groundDraw();
                fgcolor(0);

                for (numMinerals = 0; numMinerals < 25; numMinerals++) {
                        createMineral(minerals, numMinerals);
                }

                drawMinerals(minerals, numMinerals);

                initSpaceShip(ship, 115, 54, 30);
                numAliens = 0;

                addfuel(ship,buffer);
                addLives(ship, buffer);
                where = 2;

            break;

            case 2:

                    if (getSpawnRateFlag() >= 500 && spawnRate > 10){
                            spawnRate--;
                            resetSpawnRateFlag();
                            gotoxy(1,1);
                            printf("%d", spawnRate);
                    }


                    if (getAlienFlag() >= 10) {
                        if (numAliens <= 20){
                            if(spawnAlien(aliens, numAliens, spawnRate)) {
                                    numAliens++;






                            }
                        }
                        updateAliens(aliens,ship ,numAliens, buffer);
                        resetAlienFlag();
                    }

                    if (uart_get_count() > 0) {
                        dirct = uart_get_char();
                        uart_clear();

                    }
                    if (dirct == 'b') {
                            where = 4;
                            //oldWhere = 2;
                    }
                    pos = inBounds(ship);
                    updateVelocity(ship, dirct, buffer, pos );
                    mineralIndex = drill(ship, dirct,pos, minerals, numMinerals, buffer);
                    if (mineralIndex) {
                            mineralKilled(minerals, mineralIndex, numMinerals);
                            numMinerals--;
                    }


                    if ( (( ((*ship).vy != 0) || ((*ship).vx != 0) ) || pos == 0) && getShipFlag3() > 4){

                            updateSpaceShip(ship);
                            if (collide(aliens, ship, numAliens, buffer)) {
                                    numAliens--;
                            }
                            resetShipFlag3();
                    }


                    if (dirct==' '){
                            createBall(cannonBalls, numBalls, ship);
                            numBalls++;
                    }
                    else if (dirct == 'g' && (*ship).powerUp > 0) {
                            createPowerBullet(powerBullets, numPowerBullets, ship);
                            numPowerBullets++;
                            (*ship).powerUp--;
                    }
                    if (getBulletFlag() >= 8) {


                            score--;

                                    gotoxy(115,1);
                                    printf("%03d", score);


                        for (i=0; i<numBalls; i++){
                                updateBallPosition(&(cannonBalls[i]));

                                killedAliens = hitAliens(aliens, cannonBalls, numAliens, numBalls);
                                numAliens -= killedAliens;
                                if (killedAliens) {
                                        score += 50;
                                }


                                if((!inBallBounds(&(cannonBalls[i]))) || killedAliens) {
                                       ballKilled(cannonBalls, i, numBalls);
                                       numBalls--;


                                }
                        }

                        for (i=0; i< numPowerBullets; i++){
                                updatePowerBulletPosition(&(powerBullets[i]));

                                killedAliens = powerHitAliens(aliens, powerBullets, numAliens, numPowerBullets);
                                numAliens -= killedAliens;
                                if (killedAliens) {
                                        score += 50;
                                }


                                if((!inPowerBulletBounds(&(powerBullets[i])))) {
                                       powerBulletKilled(powerBullets, i, numPowerBullets);
                                       numPowerBullets--;

                                }
                        }


                        resetBulletFlag();
                    }
                    endgame = endGameCondition(ship, minerals,numMinerals);
                    if (endgame){

                        where = 3;
                    }
                    dirct = 0x0D;


                    break;


            case 3:
                    gameOver(endgame, score);
                    where = 1;
                    break;
            case 4:
                    start_stop();
                    bossKey();

                    //where = oldWhere;
                   // if (where == 2) {
                        clrscr();
                        drawLandscape();
                        groundDraw();
                        drawMinerals(minerals, numMinerals);
                        drawShip((*ship).x, (*ship).y);
                        where = 2;
                        fgcolor(0);
                        start_stop();
                    //}
                    break;

        }
    }
}



















/*

   char *text = calloc(100, sizeof(char));
    int i;
    char *s = calloc(256, sizeof(char));
    rollingtext_t *test;


    char textStr[10];

    LED_setup();
    joystick_setup();
    setup_pot();

    set_timer();
    start_stop();


    lcd_init();


    color(0,7);
    clrscr();

    memset(buffer, 0x00, 512);

    lcd_push_buffer(buffer);



    while(1){



       // printf("%d\n",readPotLeft());
        //measPot(readPotLeft());
        //printf("\n\n");
        measPot(readPotLeft(), &textStr);

        printf("%s", textStr );

        //printf("%s\n", textStr);
        lcd_write_string(textStr, buffer, 1 ,1);



        lcd_push_buffer(buffer);

        for (i=0; i<4000000; i++){}

    }
}


*/
