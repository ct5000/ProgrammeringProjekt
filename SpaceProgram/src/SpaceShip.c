#include "SpaceShip.h"


void initSpaceShip(SpaceShip_t *ship, int32_t x, int32_t y, int16_t fuel) {
    (*ship).x=x;
    (*ship).y=y;
    (*ship).vx = 0;
    (*ship).vy = 0;
    (*ship).lives = 5;
    (*ship).fuel=fuel;
    drawShip(x,y);
}

void updateSpaceShip(SpaceShip_t * ship){
    int8_t bounds;
    deleteAlien((*ship).x,(*ship).y);
    (*ship).x += (*ship).vx;
    (*ship).y += (*ship).vy;
    bounds = inBounds(ship);
    switch (bounds) {
        case 1:
            (*ship).x = 2;
            (*ship).vx = 0;
            break;
        case 2:
            (*ship).x = SCREEN_WIDTH - 1;
            (*ship).vx = 0;
            break;
        case 3:
            (*ship).y = GROUND_HEIGHT - 2;
            (*ship).vy = 0;
            break;
        case 4:
            (*ship).y = 1;
            (*ship).vy = 0;
            break;
        case 5:
            (*ship).y = GROUND_HEIGHT - 2;
            (*ship).vy = 0;
            (*ship).x = 2;
            (*ship).vx = 0;
            break;
        case 6:
            (*ship).y = GROUND_HEIGHT - 2;
            (*ship).vy = 0;
            (*ship).x = SCREEN_WIDTH - 1;
            (*ship).vx = 0;
            break;
        case 7:
            (*ship).y = 2;
            (*ship).vy = 0;
            (*ship).x = 2;
            (*ship).vx = 0;
            break;
        case 8:
            (*ship).y = 2;
            (*ship).vy = 0;
            (*ship).x = SCREEN_WIDTH - 1;
            (*ship).vx = 0;
            break;
        default:
            break;
    }


	//drawSymbol((*ship).x,(*ship).y, 'A');
	drawShip((*ship).x, (*ship).y);

	gotoxy(91,5);

	printf("fuel: %3d", (*ship).fuel);

}

void updateVelocity(SpaceShip_t * ship, char dirct) {
    if (dirct == 'w' && (*ship).fuel>0){
        (*ship).vy -= 2;
        (*ship).fuel--;
        subfuel(ship);
    }
    else if (dirct == 'a' && (*ship).fuel>0){
        (*ship).vx -= 2;
        (*ship).fuel--;
        subfuel(ship);
    }
    else if (dirct == 'd' && (*ship).fuel>0){
        (*ship).vx += 2;
        (*ship).fuel--;
        subfuel(ship);
    }
    else {
        (*ship).vy++;
        if ((*ship).vx > 0) {
            (*ship).vx--;
        }
        else if ((*ship).vx < 0) {
            (*ship).vx++;
        }
	}
}


int8_t inBounds(SpaceShip_t *p){
//f�lgende er de forskellige tilf�lde den kan overstige gr�nserne

    //hver af returv�rdierne svarer til at frakoble en bestemt tast



    //Spilleren er i nederste venstre hj�rne
    if ((*p).x <= 1 && (*p).y >= GROUND_HEIGHT - 2) {
        return 5;
    }
    //Spilleren er i nederste h�jre hj�rne
    else if ((*p).x >= SCREEN_WIDTH - 1 && (*p).y >= GROUND_HEIGHT - 2) {
        return 6;
    }
    //Spilleren er i �verste venstre hj�rne
    else if ((*p).x <= 1 && (*p).y <= 2) {
        return 7;
    }
    //Spilleren er i �verste h�jre hj�rne
    else if ((*p).x >= SCREEN_WIDTH - 1 && (*p).y <= 2) {
        return 8;
    }
    //skibet er for langt til venstre
    else if ((*p).x<=1){
        return 1;
    }
    //skibet er for langt til h�jre
    else if ((*p).x>=SCREEN_WIDTH - 1){
        return 2;
    }
    //spilleren fors�ger at grave sig ned i jorden
    else if ((*p).y>=GROUND_HEIGHT - 2){
        return 3;
    }
    //spilleren flyver ud af banen
    else if ((*p).y < 2){
       return 4;
    }
    return 0;
}

//Skibets drill til at f� mineraler
void drill(SpaceShip_t * ship, char dirct, int8_t place, mineral_t minerals[], int numMinerals){
	int i;
	int j;

	if ((dirct == 'e' || dirct == 'E')  && place == 3){ //Hvis der trykkes 'e' og skibet st�r p� jorden,

            i = checkMinerals(ship, minerals, numMinerals); //mineralets placering

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

//l�gger fuel til fuelbaren
void addfuel(SpaceShip_t * ship){
    int i;
        fgcolor(0);
        gotoxy(1,1);
        for(i=0; i < (*ship).fuel; i++){
            gotoxy(i,1);
            printf("%c",219);
        }
}

//Tr�kker fuel fra fuelbaren
void subfuel(SpaceShip_t * ship){
        gotoxy((*ship).fuel+1,1);
            printf(" ");
}

// Finder det mineral skibet st�r over
int checkMinerals(SpaceShip_t *ship, mineral_t minerals[], int numMinerals){
    int i;
        for (i=1; i<numMinerals; i++){

            if ((*ship).x == (minerals[i - 1]).x){
            return i;

            }

        }
    return 0;

}
