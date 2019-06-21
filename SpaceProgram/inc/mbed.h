#ifndef MBED_H
#define MBED_H

#include "stm32f30x_rcc.h"
#include "serialRead.h"

#include <string.h>
#include <stdio.h>


int8_t readJoystick();
void showDirection(int8_t old, int8_t next);
void writeLED(int8_t ledcolor);
void showColor(int8_t joystick);

void setTimer();
void TIM2_IRQHandler(void);

int getTime();
int getSec();
int getMin();

void resetTime();
void startStop();

int split_time1();

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

void setupPot();
int16_t readPotLeft();
int16_t readPotRight();
void measPot(int32_t read, char *s);


void setupLED();
void joystick_setup();
#endif

