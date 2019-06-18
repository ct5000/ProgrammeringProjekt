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
#include "aliens.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ESC 0x1B




int main(void){
    alien_t aliens[25];
<<<<<<< HEAD
    uart_init(96000);
    color(7,0);
    int8_t numAliens = 0;
    int p=0;
    int i;
    cannonBall_t ammo[50];

    runningMenu();
    //setup_pot();


    clrscr();


=======
    int8_t numAliens = 0;
<<<<<<< HEAD
=======
    char dirct;
//    runningMenu();
    //setup_pot();
>>>>>>> 1f5604dbb0850c25fae6b73a712675310ecb9aaa

    mineral_t minerals[25];
    int8_t numMinerals = 0;
    uart_init(96000);
    color(7,0);
<<<<<<< HEAD



    set_timer();
    start_stop();
    runningMenu();
    srand(getTime());
    resetTime();
    start_stop();
=======
>>>>>>> 6c1060c210c2341417bf0915076d40034612bc4c
    //runningMenu();
    set_timer();
    start_stop();
    drawLandscape();
    groundDraw();
    //drawHills();
    fgcolor(0);
>>>>>>> 1f5604dbb0850c25fae6b73a712675310ecb9aaa

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






    while(1){
            if(spawnAlien(aliens, numAliens)) {
                    numAliens++;
            }
            updateAliens(aliens, numAliens);

<<<<<<< HEAD
            dirct = uart_get_char();
||||||| merged common ancestors
            char dirct = uart_get_char();
=======
<<<<<<< HEAD
            if(spawnAlien(aliens, numAliens)) {
                    numAliens++;
            }
            updateAliens(aliens, numAliens);
=======
            char dirct = uart_get_char();
>>>>>>> 999ec77e69105d45b8fb397ab04c3214ccdfc59b

            updateVelocity(ship, dirct);
<<<<<<< HEAD
            updateSpaceShip(ship, inBounds(ship));
            drill(ship, dirct,inBounds(ship), minerals);
=======
            pos = inBounds(ship);
            updateSpaceShip(ship);

            drill(ship, dirct,pos, minerals);
>>>>>>> 1f5604dbb0850c25fae6b73a712675310ecb9aaa


           // updatefuelBar(ship, dirct);

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


>>>>>>> 6c1060c210c2341417bf0915076d40034612bc4c

            char dirct = uart_get_char();

            updateVelocity(ship, dirct);
            updateSpaceShip(ship, dirct, inBounds(ship));
            drill(ship, dirct,inBounds(ship), minerals);

             if (uart_get_count() > 0) {

               if (uart_get_char()=='g'){
                    p++;
                    initCannon(&(ammo[p]), &ship);
               }
            }
            for (i=0; i<=p; i++){
                if (inBallBounds(&(ammo[p]))){
                    updateBallPosition(&(ammo[p]));
                    if (killAliens())
                }
                else {
                    deleteSymbol((ammo[p]).x >>14, (ammo[p]).y>>14);
                }
                   // updatefuelBar(ship, dirct);
            }




}


