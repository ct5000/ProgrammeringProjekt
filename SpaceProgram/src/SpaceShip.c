#include "SpaceShip.h"


void initSpaceShip(SpaceShip_t *ship, int32_t x, int32_t y, int16_t fuel) {
    (*ship).x=x;
    (*ship).y=y;
    (*ship).vx = 0;
    (*ship).vy = 0;
    (*ship).lives = 5;
    (*ship).fuel=fuel;
    (*ship).powerUp = 0;
    drawShip(x,y);
}

void updateSpaceShip(SpaceShip_t * ship){
    int8_t bounds;

    deleteAlien((*ship).x,(*ship).y);
    //if (getShipFlag3() > 4) {
        (*ship).x += (*ship).vx;
       // resetShipFlag3();
    //}
    if (getShipFlag2() > 2){
        (*ship).y += (*ship).vy;
        resetShipFlag2();
    }
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
	drawShip((*ship).x, (*ship).y);

	//gotoxy(1,1);

	//printf("fuel: %3d", (*ship).fuel);

}

void updateVelocity(SpaceShip_t * ship, char dirct, uint8_t *buffer, int place) {

    if (dirct == 'a' && (*ship).fuel>0){
        if ((*ship).vx > -3) {
            (*ship).vx -= 1;
            (*ship).fuel--;
            subfuel(ship, buffer);
        }
    }
    else if (dirct == 'd' && (*ship).fuel>0){
        if ((*ship).vx < 3) {
            (*ship).vx += 1;
            (*ship).fuel--;
            subfuel(ship, buffer);
        }
    }
    else if (dirct == 'w' && (*ship).fuel>0){
        if ((*ship).vy > -3) {
            (*ship).vy -= 1;
            (*ship).fuel--;
            subfuel(ship, buffer);
        }
    }
    else if (place == 3){
        (*ship).vx = 0;
        (*ship).vy =0;
    }
    else if (getShipFlag1() > 20) {
            if ((*ship).vy < 1) {
            (*ship).vy++;
            }
            resetShipFlag1();



        if ((*ship).vx > 0) {
            (*ship).vx--;
        }
        else if ((*ship).vx < 0) {
            (*ship).vx++;
        }
	}
}


int8_t inBounds(SpaceShip_t *p){
//følgende er de forskellige tilfælde den kan overstige grænserne

    //hver af returværdierne svarer til at frakoble en bestemt tast
    //Spilleren er i nederste venstre hjørne
    if ((*p).x <= 1 && (*p).y >= GROUND_HEIGHT - 2) {
        return 5;
    }
    //Spilleren er i nederste højre hjørne
    else if ((*p).x >= SCREEN_WIDTH - 1 && (*p).y >= GROUND_HEIGHT - 2) {
        return 6;
    }
    //Spilleren er i øverste venstre hjørne
    else if ((*p).x <= 1 && (*p).y <= 2) {
        return 7;
    }
    //Spilleren er i øverste højre hjørne
    else if ((*p).x >= SCREEN_WIDTH - 1 && (*p).y <= 2) {
        return 8;
    }
    //skibet er for langt til venstre
    else if ((*p).x<=1){
        return 1;
    }
    //skibet er for langt til højre
    else if ((*p).x>=SCREEN_WIDTH - 1){
        return 2;
    }
    //spilleren forsøger at grave sig ned i jorden
    else if ((*p).y>=GROUND_HEIGHT - 2){
        return 3;
    }
    //spilleren flyver ud af banen
    else if ((*p).y < 2){
       return 4;
    }
    return 0;
}

//Skibets drill til at få mineraler
void drill(SpaceShip_t * ship, char dirct, int8_t place, mineral_t minerals[], int numMinerals, uint8_t *buffer){
	int i;
	int j;

	if ((dirct == 'e' || dirct == 'E')  && place == 3){ //Hvis der trykkes 'e' og skibet står på jorden,

            i = checkMinerals(ship, minerals, numMinerals); //mineralets placering

            if (i){ //Hvis skibet er over et mineral

                (*ship).fuel += (*minerals).fuel;
                (*ship).powerUp += (*minerals).powerUp;

                for (j = GROUND_HEIGHT; j <= (minerals[i - 1]).y; j++ ){
                    gotoxy((*ship).x, j);
                    printf("%c",186);
                }
                for (j = (minerals[i - 1]).y; j >= GROUND_HEIGHT; j-- ){
                    gotoxy((*ship).x, j);
                    printf("%c",219);
                }

                addfuel(ship,buffer); //printer fuel på lcd.

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
void addfuel(SpaceShip_t * ship, uint8_t *buffer){
    int i;

        gotoxy(1,1);
        for(i=0; i < (*ship).fuel; i++){

        lcd_write_bar("E", buffer, 0,25+i);

        lcd_push_buffer(buffer);

       // lcd_push_buffer(buffer);
        }
}

//Trækker fuel fra fuelbaren
void subfuel(SpaceShip_t * ship, uint8_t *buffer){

        lcd_write_bar(" ", buffer, 0,25+(*ship).fuel);

        lcd_push_buffer(buffer);

}

// Finder det mineral skibet står over
int checkMinerals(SpaceShip_t *ship, mineral_t minerals[], int numMinerals){
    int i;
        for (i=1; i<numMinerals; i++){

            if ((*ship).x == (minerals[i - 1]).x){
            return i;
            }
        }
    return 0;
}

//Lægger liv til livbaren
void addLives(SpaceShip_t * ship, uint8_t *buffer){
    int i;

        for(i=0; i < (*ship).lives; i++){

        lcd_write_string("<3", buffer, 1,30+((i*5)*2));

        lcd_push_buffer(buffer);
        }
}

//Trækker live fra livbaren
void subLives(SpaceShip_t * ship, uint8_t *buffer){
        (*ship).lives--;
        lcd_write_string(" ", buffer, 1,30+(((*ship).lives*5)*2));
        lcd_write_string(" ", buffer, 1,35+(((*ship).lives*5)*2));

        lcd_push_buffer(buffer);
}

int8_t endGameCondition(SpaceShip_t *ship, mineral_t minerals[], int numMinerals){
    if ((*ship).fuel== 0 &&  (checkMinerals(ship, minerals, numMinerals) == 0)){
            return 2;
    }
    else if ( (*ship).lives == 0){
            return 3;
    }
    else if ( (*ship).y < 3){
            return 1;
    }
    return 0;
}



