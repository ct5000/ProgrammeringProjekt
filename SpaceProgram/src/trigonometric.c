#include "trigonometric.h"
#include <stdio.h>

int32_t Sin(int grader){
    //float graderF;
    //grader %= 360;
    //grader += 360;
    //grader %= 360;
    //graderF = (float) grader;
    //return SIN[(int)(graderF/360*512)];

    int grader2 = (512*grader)/360;
    return SIN[grader2 & 0x1FF];
}
int32_t Cos(int grader){
    return Sin(grader + 90);

    }
void printFix(int32_t i) {
 // Prints a signed 16.16 fixed point number
    if ((i & 0x80000000) != 0) { // Handle negative numbers
        printf("-");
        i = ~i + 1;
    }

    printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
 // Print a maximum of 4 decimal digits to avoid overflow
 }
int32_t expand(int32_t i) {
 // Converts an 18.14 fixed point number to 16.16
 return i << 2;
 }

