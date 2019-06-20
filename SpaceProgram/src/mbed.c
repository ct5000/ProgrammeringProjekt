#include "mbed.h"


/*  blue - D8 - CN5 - 1
    green - D9 - CN5 - 2
    red - D5 - CN9 - 6

    right - A5 - CN8 - 6
    up - A2 - CN8 - 3
    mid - d4 - CN9 - 5
    left - A4 - CN8 - 5
    down - A3 - CN8 - 4

    reset values page. 170.
*/

    int time =0;
    int alienFlag =0;
    int bulletFlag = 0;
    int shipFlag1 = 0;
    int shipFlag2 = 0;
    int shipFlag3 = 0;

void LED_setup(){

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

void joystick_setup(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    // Set pin PA4 to input
    GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
    GPIOA->PUPDR |= (0x00000001 << (4 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C
    // Set pin PC0 to input
    GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
    GPIOC->PUPDR |= (0x00000001 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    // Set pin PC1 to input
    GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
    GPIOC->PUPDR |= (0x00000001 << (1 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    // Set pin PB5 to input
    GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
    GPIOB->PUPDR |= (0x00000001 << (5 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    // Set pin PB0 to input
    GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
    GPIOB->PUPDR |= (0x00000001 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)
}

int8_t readJoystick(){

    // UP
    uint16_t upVal = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4


    // Right
    uint16_t rightVal = GPIOC->IDR & (0x0001 << 0); //Read from pin PA4


    // left
    uint16_t leftVal = GPIOC->IDR & (0x0001 << 1); //Read from pin PA4


    // center
    uint16_t centerVal = GPIOB->IDR & (0x0001 << 5); //Read from pin PA4


    // Down
    uint16_t downVal = GPIOB->IDR & (0x0001 << 0); //Read from pin PA4

    if (upVal){
        return 0b00000001;
    }
    else if (downVal){
        return 0b00000010;
    }
    else if (leftVal){
        return 0b00000100;
    }
    else if (rightVal){
        return 0b00001000;
    }
    else if (centerVal){
        return 0b00010000;
    }
    else{
    return 0;
    }


}

void showDirection(int8_t old, int8_t next){

    char *s;

    if (old != next && next > 0){
            switch(next){
            case 1:
                s = "Up";
                break;
            case 2:
                s = "Down";
                break;
            case 4:
                s = "Left";
                break;
            case 8:
                s = "Right";
                break;
            case 16:
                s = "Center";
                break;
            }
        printf("%s\n", s);
    }
}

void writeLED(int8_t ledcolor){

    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C


    switch(ledcolor){
        case 0:
        // off
            GPIOA->ODR |= (0x0001 << 9);
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
            break;

        case 1:
            //red
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to high
            break;

        case 2:
            //green
            GPIOA->ODR |= (0x0001 << 9);
            GPIOC->ODR &= ~(0x0001 << 7);
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
            break;

            case 3:
            //yellow
            GPIOA->ODR |= (0x0001 << 9);
            GPIOC->ODR &= ~(0x0001 << 7);
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to high
            break;

         case 4:
             //blue
            GPIOA->ODR &= ~(0x0001 << 9);
            GPIOC->ODR |= (0x0001 << 7);
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
            break;

         case 5:
             //purple
            GPIOA->ODR &= ~(0x0001 << 9);
            GPIOC->ODR |= (0x0001 << 7);
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to high
            break;

        case 6:
            GPIOA->ODR &= ~(0x0001 << 9);
            GPIOC->ODR &= ~(0x0001 << 7);
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to high
            break;

        case 7:
            //white

            break;
        }
}

void showColor(int8_t joystick){

    switch(joystick){
            case 1:
                writeLED(1);
                break;
            case 2:
                writeLED(2);
                break;
            case 4:
                writeLED(3);
                break;
            case 8:
                writeLED(4);
                break;
            case 16:
                writeLED(5);
                break;
            case 0:
                writeLED(0);
                break;
            default:
                break;

            }
}

void set_timer(){


     RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;

     TIM2->CR1 = 0x00000000; // Configure timer 2
     TIM2->ARR = 0x3CF9; // Set reload value = 15609
     TIM2->PSC = 0x028; // Set prescale value = 40

     TIM2->DIER |= 0x0001; // Enable timer 2 interrupts

     NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
     NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt


}

void start_stop(){
    if (TIM2->CR1 & 0x01){
        TIM2->CR1 = 0x00; //starts timer
    }
    else {
        TIM2->CR1 = 0x01;
    }
}

void resetTime(){
    if (TIM2->CR1 & 0x01){
        TIM2->CR1 = 0x00; //starts timer
    }
    time = 0;
}

int split_time1(){
    return time;
}

void TIM2_IRQHandler(void) {
    alienFlag++;
    bulletFlag++;
    shipFlag1++;
    shipFlag2++;
    shipFlag3++;
    time++;
    TIM2->SR &= ~0x0001; // Clear interrupt bit
 }

int getAlienFlag() {
    return alienFlag;
 }

void resetAlienFlag() {
    alienFlag = 0;
}

int getShipFlag1() {
    return shipFlag1;
 }

void resetShipFlag1() {
    shipFlag1 = 0;
}

int getShipFlag2() {
    return shipFlag2;
 }

void resetShipFlag2() {
    shipFlag2 = 0;
}

int getShipFlag3() {
    return shipFlag3;
 }

void resetShipFlag3() {
    shipFlag3 = 0;
}


int getBulletFlag() {
    return bulletFlag;
 }

void resetBulletFlag() {
    bulletFlag = 0;
}

int getTime(){
    return(time%100);
}

int getSec(){
    return((time/100)%60);
}

int getMin(){
    return((time/(100*60)%60));
}

int gethour(){
    return(time/(100*60*60));
}


void setup_pot(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    // Set pin PA4 to input
    GPIOA->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

    // Set pin PA4 to input
    GPIOA->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
   // GPIOA->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
    //GPIOA->PUPDR |= (0x00000001 << (1 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)



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

int16_t readPotLeft(){

    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);

    ADC_StartConversion(ADC1); // Start ADC read
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

    uint16_t x = ADC_GetConversionValue(ADC1); // Read the ADC value

    return x;

}

int16_t readPotRight(){

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);

    ADC_StartConversion(ADC1); // Start ADC read
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

    uint16_t y = ADC_GetConversionValue(ADC1); // Read the ADC value

    return y;

}

void measPot(int32_t read, char *s){
    //char num[7];
    //char textStr[7];

    int32_t g = read / 1242;
    int32_t deci = (read % 1242) * 8;
    sprintf(s,"%ld,%04ld",g, deci);


    //strcpy(textStr ,num);
    //return textStr;
//return num;
  //  printf("\n %ld.%04ld", read >> 10, 10000 * (uint32_t)(read & 0xFFFF) >> 10);
 // Print a maximum of 4 decimal digits to avoid overflow
 }



