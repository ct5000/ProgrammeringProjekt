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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define ESC 0x1B





int main(void){
    uart_init(9600);
    clrscr();
    bgcolor(6);

    setup_pot();
    int i;
    int q;

    srand(q); //skal afhænge af en tids værdi



    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;

    initSpaceShip(ship, 5, 5, 100);

    drawfuelBar(ship);

    drawLandscape();

    mineral_t m1;
    mineral_t m2;
    mineral_t m3;



    initMineral(&m1);
    initMineral(&m2);
    initMineral(&m3);

    mineral_t minerals[] = {m1,m2,m3};

    drawMinerals(minerals);


    while(1){

    char dirct = uart_get_char();
    updateSpaceShip(ship, dirct, inBounds(ship));
    drill(ship, dirct, inBounds(ship));

    usefuelBar(ship, dirct);
    if (uart_get_count() > 2) {
            uart_clear();
    }




    }
}
















