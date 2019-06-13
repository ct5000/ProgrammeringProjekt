
#include "vectors.h"
#include "ball.h"
#include <stdio.h>
#include "ansi.h"

#define FIX14_SHIFT 14

void initBall(ball_t *ball, int32_t x, int32_t y, int32_t vx, int32_t vy) {
    (*ball).x=x;
    (*ball).y=y;
    (*ball).vx=vx;
    (*ball).vy=vy;
    drawSymbol(x,y,'o');
}

void updatePosition(ball_t * ball){
	int prevX = (*ball).x;
	int prevY = (*ball).y;

	deleteSymbol(prevX,prevY);

	(*ball).x += (*ball).vx;
	(*ball).y += (*ball).vy;
	drawSymbol((*ball).x,(*ball).y, 'o');

}
void bounceBall(ball_t *ball, int collisionType) {
	switch(collisionType) {
		case 1:
			(*ball).vx = (-1) * (*ball).vx;
			break;
		case 2:
			(*ball).vx = (-1) * (*ball).vx;
			break;
		case 3:
			(*ball).vy = (-1) * (*ball).vy;
			break;
		case 4:
			(*ball).vy = (-1) * (*ball).vy;
			break;
		default:
			break;
	}
}
int checkColl(ball_t *ball, int x1, int y1, int x2, int y2) {
	if ((*ball).x >= x2-1) {
		return 1;
	}
	else if((*ball).x <= x1+1) {
		return 2;
	}
	else if((*ball).y >= y2-1) {
		return 3;
	}
	else if((*ball).y <= y1+1) {
		return 4;
	}
	else {
		return 0;
	}
}
