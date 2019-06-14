#include "SpaceShip.h"
#include <string.h>

void initSpaceShip(SpaceShip_t *ship, int32_t x, int32_t y, int8_t fuel) {
    (*ship).x=x;
    (*ship).y=y;
    (*ship).fuel=fuel;
    drawSymbol(x,y,'A');
}

void updateSpaceShip(SpaceShip_t * ship, char dirct, int8_t place){
	int prevX = (*ship).x;
	int prevY = (*ship).y;
	int fuel;
	int i;


        if (dirct == 'w' && (*ship).fuel>0){          //up
                (*ship).y--;
                (*ship).fuel--;
                deleteSymbol(prevX,prevY);
        }
        else if (dirct == 'a' && (*ship).fuel>0){     //left
                (*ship).x--;
                (*ship).fuel--;
                deleteSymbol(prevX,prevY);
        }
        else if (dirct == 'd' && (*ship).fuel>0){     //right
                (*ship).x++;
                (*ship).fuel--;
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
	gotoxy(115,5);

	printf("fuel: %3d", (*ship).fuel);

}

void drill(SpaceShip_t * ship, char dirct, int8_t place){
	int i;

	if (dirct == 'e' && place == 3){
        for (i = 0; i <= 76; i++ ){
            gotoxy((*ship).x, 56+i);
                printf("%c",186);
        }
        for (i = 76; i >= 0; i-- ){
                gotoxy((*ship).x, 56+i);
                printf("%c",219);
        }


	}

}
void drawfuelBar(SpaceShip_t * ship){
    int i;
    gotoxy(1,1);
    for (i=0; i < (*ship).fuel; i++){
        printf("%c",219);
    }
}

void usefuelBar(SpaceShip_t * ship, char dirct){
    int i;
    if (dirct == 'w' || 'a' || 'd'){
            gotoxy((*ship).fuel+1,1);
            printf(" ");
    }




}


