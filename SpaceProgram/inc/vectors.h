

#ifndef VECTORS_H
#define VECTORS_H

#include <stdio.h>
#include "LUTsin.h"
#include "trigonometric.h"
#include <stdint.h>

#define FIX14_SHIFT 14

#define FIX14_MULT(a,b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a,b) ( ((a) << FIX14_SHIFT) / b)

typedef struct {
    int32_t x ,y;
} vector_t;

void rotateVector(vector_t *vec, int grader);
void initVector(vector_t *vec, int32_t x, int32_t y);

#endif

