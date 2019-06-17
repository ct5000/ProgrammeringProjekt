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
#include "Cannon.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ESC 0x1B





int main(void){
<<<<<<< HEAD

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


=======
    int pos;
    uint8_t buffer[512];
    uart_init(96000);

    lcd_init();



    memset(buffer, 0x00, 512);

    lcd_push_buffer(buffer);

    color(7,0);
    //runningMenu();
    set_timer();
    start_stop();
    drawLandscape();
    fgcolor(0);
>>>>>>> 8924af2ff669864e805cdb915595bd8189b1a588



    //setup_pot();

    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;
    initSpaceShip(ship, 5, 5, 100);

    mineral_t m1;
    mineral_t m2;
    mineral_t m3;

    initMineral(&m1);
    initMineral(&m2);
    initMineral(&m3);

    mineral_t minerals[] = {m1, m2, m3};

    drawMinerals(minerals);




    addfuel(ship);






    while(1){

<<<<<<< HEAD
    char dirct = uart_get_char();
    updateSpaceShip(ship, dirct, inBounds(ship));
    drill(ship, dirct);
    */

    while(1){
    if (uart_get_count() > 0) {

       if (uart_get_char()=='g'){
            p++;
            initCannon((&ammo[p]), &spac);
       }
    }
    for (i=0; i<=p; i++){
        if (inBallBounds((&ammo[p]))){
            updateBallPosition((&ammo[p]));
        }
        else {
            deleteSymbol((ammo[p]).x >> 14,(ammo[p]).y >> 14);
        }
    }

    }
=======
>>>>>>> 8924af2ff669864e805cdb915595bd8189b1a588


        char dirct = uart_get_char();
        updateSpaceShip(ship, dirct, inBounds(ship));
        pos = inBounds(ship);
        drill(ship, dirct,pos, minerals);

        lcd_write_string("2", buffer, 2,2);
        lcd_push_buffer(buffer);

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
