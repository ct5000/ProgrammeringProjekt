#include "LUTsin.h"
#include "trigonometric.h"
#include <stdio.h>
#include <stdint.h>

#ifndef BALL_H
#define BALL_H

typedef struct {
    int32_t x, y, vx, vy;
} ball_t;

void updatePosition(ball_t * ball);
void bounceBall(ball_t *ball, int collisionType);
void initBall(ball_t *ball, int32_t x, int32_t y, int32_t vx, int32_t vy);
int checkColl(ball_t *ball, int x1, int y1, int x2, int y2);
#endif



