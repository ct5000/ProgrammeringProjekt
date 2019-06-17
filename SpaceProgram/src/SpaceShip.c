#include "SpaceShip.h"


void initSpaceShip(SpaceShip_t *ship, int32_t x, int32_t y, int16_t fuel) {
    (*ship).x=x;
    (*ship).y=y;
    (*ship).fuel=fuel;
    drawSymbol(x,y,'A');
}

void updateSpaceShip(SpaceShip_t * ship, char dirct, int8_t place){
	int prevX = (*ship).x;
	int prevY = (*ship).y;


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
	gotoxy(91,5);

	printf("fuel: %3d", (*ship).fuel);

}

int8_t inBounds(SpaceShip_t *p){
//følgende er de forskellige tilfælde den kan overstige grænserne

    //hver af returværdierne svarer til at frakoble en bestemt tast
    //skibet er for langt til venstre
    if ((*p).x<=0){
        return 1;
    }
    //skibet er for langt til højre
    else if ((*p).x>=SCREEN_WIDTH){
        return 2;
    }
    //spilleren forsøger at grave sig ned i jorden
    else if ((*p).y==GROUND_HEIGHT-1){
        return 3;
    }
    //spilleren flyver ud af banen
    else if ((*p).y>SCREEN_HEIGHT){
       return 4;
    }
    return 0;
}

void drill(SpaceShip_t * ship, char dirct, int8_t place){
	int i;

	if (dirct == 'e' && place == 3){
        for (i = 0; i <= SCREEN_HEIGHT; i++ ){
            gotoxy((*ship).x, GROUND_HEIGHT+i);
                printf("%c",186);
        }
        for (i = SCREEN_HEIGHT; i >= 0; i-- ){
                gotoxy((*ship).x, GROUND_HEIGHT+i);
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
    if (dirct == 'w' || 'a' || 'd'){
            gotoxy((*ship).fuel+1,1);
            printf(" ");
    }




}


