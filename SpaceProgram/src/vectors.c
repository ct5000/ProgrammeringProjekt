#include "vectors.h"


void initVector(vector_t *vec, int32_t x, int32_t y){
    (*vec).x = x << FIX14_SHIFT;
    (*vec).y = y << FIX14_SHIFT;
}

void rotateVector(vector_t *vec, int grader){
    int32_t tempx = (*vec).x;
    (*vec).x = FIX14_MULT((*vec).x,Cos(grader))-FIX14_MULT((*vec).y,Sin(grader));
    (*vec).y = FIX14_MULT(tempx,Sin(grader))+FIX14_MULT((*vec).y,Cos(grader));
}

