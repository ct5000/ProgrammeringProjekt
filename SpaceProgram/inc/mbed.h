#ifndef MBED_H
#define MBED_H

#include "stm32f30x_rcc.h"

#include <string.h>
#include <stdio.h>

#define PRESCALER_VALUE 9

void setupLED();
void writeLED(int8_t ledcolor);

void setTimer();
void TIM1_BRK_TIM15_IRQHandler(void);
void resetTime();
void startStop();
int getTime();

void setTimer2 ();
void setFreq(uint16_t freq);

int getAlienFlag();
void resetAlienFlag();
int getBulletFlag();
void resetBulletFlag();
int getShipFlag1();
void resetShipFlag1();
int getShipFlag2();
void resetShipFlag2();
int getSpawnRateFlag();
void resetSpawnRateFlag();
int getSoundFlag();
void resetSoundFlag();

void setupPot();
int16_t readPotRight();


#endif

