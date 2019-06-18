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

    cannonBall_t cannonBalls[50];
    int8_t numBalls = 0;

    int i;

    uart_init(96000);


    setup_pot();


    set_timer();
    start_stop();
    color(7,0);
    //runningMenu();
    srand(getTime());
    resetTime();
    start_stop();

    clrscr();

    drawLandscape();
    groundDraw();
    fgcolor(0);


    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;
    initSpaceShip(ship, 5, 5, 100);

    for (numMinerals = 0; numMinerals < 25; numMinerals++) {
            createMineral(minerals, numMinerals);
    }



    drawMinerals(minerals, numMinerals);




    addfuel(ship);
    //makeAlien(aliens, 0);
    //numAliens++;






    while(1){
            //if time%x
            if(spawnAlien(aliens, numAliens)) {
                    numAliens++;
            }
            updateAliens(aliens, numAliens);

            char dirct = uart_get_char();

            updateVelocity(ship, dirct);
            updateSpaceShip(ship);


            drill(ship, dirct,inBounds(ship), minerals, numMinerals);
            if (dirct=='g'){

                    createBall(cannonBalls, numBalls, ship);
                    numBalls++;

            }
            for (i=0; i<numBalls; i++){
                    updateBallPosition(&(cannonBalls[i]));

                    killedAliens = hitAliens(aliens, cannonBalls, numAliens, numBalls);
                    numAliens -= killedAliens;
                    if((!inBallBounds(&(cannonBalls[i]))) || killedAliens) {
                           ballKilled(cannonBalls, i, numBalls);
                           numBalls--;
                    }
            }

         //  gotoxy(115,8);
          //  printf("a:%d b:%2d", numAliens, numBalls);

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
