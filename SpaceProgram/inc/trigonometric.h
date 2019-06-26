#ifndef TRIGONOMETRIC_H
#define TRIGONOMETRIC_H

#include <stdio.h>
#include <stdint.h>

#include "LUTsin.h"

#define FIX14_SHIFT 14

#define FIX14_MULT(a,b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a,b) ( ((a) << FIX14_SHIFT) / b)

int32_t Sin(int grader);
int32_t Cos(int grader);

#endif

