#ifndef MBED_H
#define MBED_H

#include "stm32f30x_rcc.h"
#include "serialRead.h"

#include <string.h>
#include <stdio.h>

#define PRESCALER_VALUE 9


int8_t readJoystick();  //bruges ikke
void showDirection(int8_t old, int8_t next); //bruges ikke
void writeLED(int8_t ledcolor);
void showColor(int8_t joystick); //bruges ikke

void setTimer();
void TIM1_BRK_TIM15_IRQHandler(void);

void setTimer2 ();
void setFreq(uint16_t freq);

int getTime();
int getSec(); //bruges ikke
int getMin(); //bruges Ikke

void resetTime();
void startStop();

int split_time1(); //bruges ikke

int getAlienFlag();
void resetAlienFlag();
int getBulletFlag();
void resetBulletFlag();
int getShipFlag1();
void resetShipFlag1();
int getShipFlag2();
void resetShipFlag2();
int getShipFlag3();
void resetShipFlag3();
int getSpawnRateFlag();
void resetSpawnRateFlag();
int getSoundFlag();
void resetSoundFlag();

void setupPot();
int16_t readPotLeft(); //bruges ikke
int16_t readPotRight();
void measPot(int32_t read, char *s); //bruges ikke


void setupLED();
void joystick_setup(); //bruges ikke
#endif

