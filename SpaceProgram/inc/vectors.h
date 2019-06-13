#include "LUTsin.h"
#include "trigonometric.h"
#include <stdio.h>
#include <stdint.h>

#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
    int32_t x ,y;
} vector_t;

void rotateVector(vector_t *vec, int grader);
void initVector(vector_t *vec, int32_t x, int32_t y);

#endif

