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

    deleteAlien((*ship).x,(*ship).y);

        if (dirct == 'w' && (*ship).fuel>0){          //up
                (*ship).y--;
                (*ship).fuel--;
                subfuel(ship);

        }
        else if (dirct == 'a' && (*ship).fuel>0){     //left
                (*ship).x--;
                (*ship).fuel--;
                subfuel(ship);

        }
        else if (dirct == 'd' && (*ship).fuel>0){     //right
                (*ship).x++;
                (*ship).fuel--;
                subfuel(ship);

        }
        else {
                if (place!=3){
                //falling down due to gravity
                (*ship).y++;

                }

	}


	//drawSymbol((*ship).x,(*ship).y, 'A');
	drawShip((*ship).x, (*ship).y);

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
    else if ((*p).y==GROUND_HEIGHT-2){
        return 3;
    }
    //spilleren flyver ud af banen
    else if ((*p).y>SCREEN_HEIGHT){
       return 4;
    }
    return 0;
}

//Skibets drill til at få mineraler
void drill(SpaceShip_t * ship, char dirct, int8_t place, mineral_t minerals[]){
	int i;
	int j;

	if ((dirct == 'e' || dirct == 'E')  && place == 3){ //Hvis der trykkes 'e' og skibet står på jorden,

            i = checkMinerals(ship, minerals); //mineralets placering

            if (i){ //Hvis skibet er over et mineral

                (*ship).fuel += (*minerals).fuel;


                for (j = GROUND_HEIGHT; j <= (minerals[i - 1]).y; j++ ){
                    gotoxy((*ship).x, j);
                    printf("%c",186);
                }
                for (j = (minerals[i - 1]).y; j >= GROUND_HEIGHT; j-- ){
                    gotoxy((*ship).x, j);
                    printf("%c",219);
                }

                addfuel(ship);

            }
            else { //Hvis skibet ikke er over et mineral

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

}

//lægger fuel til fuelbaren
void addfuel(SpaceShip_t * ship){
    int i;
        fgcolor(0);
        gotoxy(1,1);
        for(i=0; i < (*ship).fuel; i++){
            gotoxy(i,1);
            printf("%c",219);
        }
}

//Trækker fuel fra fuelbaren
void subfuel(SpaceShip_t * ship){
        gotoxy((*ship).fuel+1,1);
            printf(" ");
}

// Finder det mineral skibet står over
int checkMinerals(SpaceShip_t *ship, mineral_t minerals[]){
    int i;
        for (i=1; i<4; i++){

            if ((*ship).x == (minerals[i - 1]).x){
            return i;

            }

        }
    return 0;

}
