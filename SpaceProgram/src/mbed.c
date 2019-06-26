#include "mbed.h"

    int time =0;
    int alienFlag =0;
    int bulletFlag = 0;
    int shipFlag1 = 0;
    int shipFlag2 = 0;
    int spawnRateFlag =0;
    int soundFlag =0;

/*
 * Function: setupLED
 * --------------------------
 * Setup for the LED where all it's pins are set to high for no emitting light.
 *
 *
 * returns: void
 */
void setupLED(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C
    // Set pin PA9 to output - Blue
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
    GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
    GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
    GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high
    // Set pin PC7 to output - Green
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
    GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
    GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
    GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->ODR  |= (0x0001 << 7); //Set pin PC7 to high
    // Set pin PB4 to output - Red
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
    GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
    GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
    GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
}

/*
 * Function: writeLED
 * --------------------------
 * Sets the color of the LED. 0: Off, 1: Red, 2: Green, 3: Yellow, 4: Blue
 * 5: Purple, 6: Cyan, 7: White
 *
 * ledcolor: a number for the wished color
 *
 * returns: void
 */
void writeLED(int8_t ledcolor){
    switch(ledcolor){
        case 0:
        // off
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
            break;
        case 1:
            //red
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
            break;
        case 2:
            //green
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
            break;
        case 3:
            //yellow
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
            break;
         case 4:
             //blue
            GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to low
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
            break;
         case 5:
             //purple
            GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to low
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
            break;
        case 6:
             //cyan
            GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to low
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
            break;
        case 7:
            //white
            GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to low
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
            break;
        }
}

/*
 * Function: setTimer
 * --------------------------
 * Setup for the timer but without starting it.
 *
 *
 * returns: void
 */
void setTimer(){
     RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 2;
     TIM15->CR1 = 0x0000; // Configure timer 15
     TIM15->ARR = 63999; // Set reload value
     TIM15->PSC = PRESCALER_VALUE; // Set prescale value
     TIM15->DIER |= 0x0001; // Enable timer 15 interrupts

     NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0); // Set interrupt priority
     NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt
}

/*
 * Function: startStop
 * --------------------------
 * Starts the timer.
 *
 *
 * returns: void
 */
void startStop(){
    if (TIM15->CR1 & 0x01){
        TIM15->CR1 = 0x00; //stops timer
    }
    else {
        TIM15->CR1 = 0x01; //starts timer
    }
}

/*
 * Function: resetTime
 * --------------------------
 * Resets the time time to zero and stops the timer
 *
 *
 * returns: void
 */
void resetTime(){
    TIM15->CR1 = 0x00; //stops timer
    time = 0;
}

/*
 * Function: TIM2_IRQHandler
 * --------------------------
 * Interrupt function that is called every time the timer hits a certain count. It Updates the time and the flags
 *
 *
 * returns: void
 */
void TIM1_BRK_TIM15_IRQHandler(void) {
    alienFlag++;
    bulletFlag++;
    shipFlag1++;
    shipFlag2++;
    spawnRateFlag++;
    time++;
    soundFlag++;
    TIM15->SR &= ~0x0001; // Clear interrupt bit
 }

/*
 * Function: getAlienFlag
 * --------------------------
 * Returns the value of alienFlag
 *
 *
 * returns: void
 */
int getAlienFlag() {
    return alienFlag;
 }

/*
 * Function: resetAlienFlag
 * --------------------------
 * Resets the value of alienFlag
 *
 *
 * returns: void
 */
void resetAlienFlag() {
    alienFlag = 0;
}

/*
 * Function: getShipFlag1
 * --------------------------
 * Returns the value of shipFlag1
 *
 *
 * returns: void
 */
int getShipFlag1() {
    return shipFlag1;
 }

/*
 * Function: resetShipFlag1
 * --------------------------
 * Resets the value of shipFlag1
 *
 *
 * returns: void
 */
void resetShipFlag1() {
    shipFlag1 = 0;
}

/*
 * Function: getShipFlag2
 * --------------------------
 * Returns the value of shipFlag2
 *
 *
 * returns: void
 */
int getShipFlag2() {
    return shipFlag2;
 }

/*
 * Function: resetShipFlag2
 * --------------------------
 * Resets the value of shipFlag2
 *
 *
 * returns: void
 */
void resetShipFlag2() {
    shipFlag2 = 0;
}

/*
 * Function: getSpawnRateFlag
 * --------------------------
 * Returns the value of spawnRateFlag
 *
 *
 * returns: void
 */
int getSpawnRateFlag() {
    return spawnRateFlag;
 }

/*
 * Function: resetSpawnRateFlag
 * --------------------------
 * Resets the value of SpawnRateFlag
 *
 *
 * returns: void
 */
void resetSpawnRateFlag() {
    spawnRateFlag = 0;
}

/*
 * Function: getBulletFlag
 * --------------------------
 * Returns the value of bulletFlag
 *
 *
 * returns: void
 */
int getBulletFlag() {
    return bulletFlag;
 }

/*
 * Function: resetBulletFlag
 * --------------------------
 * Resets the value of BulletFlag1
 *
 *
 * returns: void
 */
void resetBulletFlag() {
    bulletFlag = 0;
}

/*
 * Function: getSoundFlag
 * --------------------------
 * Returns the value of soundFlag
 *
 *
 * returns: void
 */
int getSoundFlag() {
    return soundFlag;
 }

/*
 * Function: resetSoundFlag
 * --------------------------
 * Resets the value of soundFlag
 *
 *
 * returns: void
 */
void resetSoundFlag() {
    soundFlag = 0;
}

/*
 * Function: getTime
 * --------------------------
 * Returns the value of time
 *
 *
 * returns: void
 */

int getTime(){
    return(time%100);
}

void setTimer2 () {
    RCC->APB1ENR |= 0x00000001; // Enable clock line to timer 2;
    TIM2->CR1 = 0x0000; // Disable timer
    TIM2->ARR = 1000; // Set auto reload value
    TIM2->PSC = PRESCALER_VALUE; // Set pre-scaler value
    TIM2->CR1 |= 0x0001; // Enable timer

    TIM2->CCER &= ~TIM_CCER_CC3P; // Clear CCER register
    TIM2->CCER |= 0x00000001 << 8; // Enable OC3 output
    TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
    TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
    TIM2->CCMR2 |= TIM_OCMode_PWM1; // Set output mode to PWM1
    TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
    TIM2->CCMR2 |= TIM_OCPreload_Enable;
    TIM2->CCR3 = 500; // Set duty cycle to 50 %

    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable clock line for GPIO bank B
    GPIOB->MODER &= ~(0x00000003 << (10 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000002 << (10 * 2)); // Set mode register
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
}


void setFreq(uint16_t freq) {
     uint32_t reload = 64e6 / freq / (PRESCALER_VALUE + 1) - 1;
     TIM2->ARR = reload; // Set auto reload value
     TIM2->CCR3 = reload/2; // Set compare register
     TIM2->EGR |= 0x01;
 }



/*
 * Function: setupPot
 * --------------------------
 * Setups the potentiometers so it is possible to read values from them.
 *
 *
 * returns: void
 */
void setupPot(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    // Set pin PA0 to input
    GPIOA->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    // Set pin PA1 to input
    GPIOA->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
    RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

    ADC1->CR = 0x00000000; // Clear CR register
    ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
    ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

    ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
    for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

    ADC1->CR |= 0x80000000; // Start ADC1 calibration
    while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
    for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

    ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
    while (!(ADC1->ISR & 0x00000001)); // Wait until ready

}

/*
 * Function: readPotRight
 * --------------------------
 * Returns the value of the Right potentiometer
 *
 *
 * returns: A value between 0 and 4095 for the voltages of the potentiometer
 */
int16_t readPotRight(){
    uint16_t x;
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1); // Start ADC read
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
    x = ADC_GetConversionValue(ADC1); // Read the ADC value
    return x;
}
