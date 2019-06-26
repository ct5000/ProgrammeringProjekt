#include "trigonometric.h"

/* Function: Sin
 * ---------------------------
 * This function determines sinus of a value by using a LUT, which was given.
 * The LUT is a 512 long array, where the value af a index corresponds to sin
 * taken of that value
 *
 * degree: The value of which sin is to be taken of
 *
 * return: an integer that is sin(degree)
 */


int32_t Sin(int degree){
    //this line converts the degree to the 512 system.
    int degree2 = (512*degree)/360;
    //& 0x1FF is to prevent overflow since complete rotations dont change the value
    //the value of the array at that degree is returned
    return SIN[degree2 & 0x1FF];
}

/* Function: Cos
 * --------------------------
 * This function determines cosinus of a function. Since cos(v)=sin(v+90) the sinus
 * function can be used.
 *
 * degree: the value of which cosinus is to determined of.
 *
 * return: return cosinus taken of the value
 */
int32_t Cos(int degree){
    return Sin(degree + 90);

    }
