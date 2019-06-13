#ifndef MBED_H
#define MBED_H

#include "stm32f30x_rcc.h"



int8_t readJoystick();
void showDirection(int8_t old, int8_t next);
void writeLED(int8_t ledcolor);
void showColor(int8_t joystick);

void set_timer();
void TIM2_IRQHandler(void);

int getTime();
int getSec();
int getMin();

void resetTime();
void start_stop();

int split_time1();

int8_t getFlag();
void rstFlag();

void setup_pot();
int16_t readPotLeft();
int16_t readPotRight();
void measPot(int32_t read, char *s);


void LED_setup();
void joystick_setup();
#endif

