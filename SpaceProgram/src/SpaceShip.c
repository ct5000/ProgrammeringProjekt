#include "SpaceShip.h"
#include <string.h>

void initSpaceShip(SpaceShip_t *ship, int32_t x, int32_t y) {
    (*ship).x=x;
    (*ship).y=y;
    drawSymbol(x,y,'A');
}

void updateSpaceShip(SpaceShip_t * ship, char dirct, int8_t place){
	int prevX = (*ship).x;
	int prevY = (*ship).y;

	if (dirct == 'w'){          //up
            (*ship).y--;
            deleteSymbol(prevX,prevY);
	}
	else if (dirct == 'a'){     //left
            (*ship).x--;
            deleteSymbol(prevX,prevY);
	}
	else if (dirct == 'd'){     //right
            (*ship).x++;
            deleteSymbol(prevX,prevY);
	}
	else {
	        if (place!=3){
            //falling down due to gravity
            (*ship).y++;
            deleteSymbol(prevX,prevY);
	        }
	}

	drawSymbol((*ship).x,(*ship).y, 'A');

}

void drill(SpaceShip_t * ship, char dirct){
    int shipx = (*ship).x;
	int shipy = (*ship).y;
	int i;

	if (dirct == 'e'){
	drawSymbol(shipx,shipy+2,'I');
	drawSymbol(shipx,shipy+3,'I');
	drawSymbol(shipx,shipy+4,'I');
	for (i=0; i<4000000; i++){}
    deleteSymbol(shipx,shipy+2);
    deleteSymbol(shipx,shipy+3);
    deleteSymbol(shipx,shipy+4);

	}

}

