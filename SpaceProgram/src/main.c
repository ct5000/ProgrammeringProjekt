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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ESC 0x1B





int main(void){
    alien_t aliens[5];
    alien_t alien;
    int8_t numAliens = 0;
    uart_init(9600);
    //runningMenu();

    clrscr();
    drawLandscape();



    bgcolor(6);
    //setup_pot();

    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;

    initSpaceShip(ship, 5, 5, 100);

    drawfuelBar(ship);
    init_alien(&alien);
    aliens[0] = alien;
    numAliens++;







    while(1){

            if(spawnAlien(aliens, numAliens)) {
                    numAliens++;
            }
            if (getFlag()== 100) {
                    alienKilled(&aliens[0]);
            }
            updateAliens(aliens, numAliens);
            char dirct = uart_get_char();
            updateSpaceShip(ship, dirct, inBounds(ship));
            drill(ship, dirct,inBounds(ship));

            usefuelBar(ship, dirct);

    }



}





















  //  char *text = calloc(100, sizeof(char));
   // int i;
    //char *s = calloc(256, sizeof(char));
    //rollingtext_t *test;
     /*
     int i;
    char textStr[10];
    uint8_t buffer[512];

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

*/

   // while(1){
/*

       // printf("%d\n",readPotLeft());
        //measPot(readPotLeft());
        //printf("\n\n");
        measPot(readPotLeft(), &textStr);
//        strcpy(textStr ,measPot(readPotLeft()));

        //printf("%s\n", textStr);
        lcd_write_string(textStr, buffer, 1 ,1);



        lcd_push_buffer(buffer);

        for (i=0; i<4000000; i++){}
            */
 //   }
//}



