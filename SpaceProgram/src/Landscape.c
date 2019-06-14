# include "Landscape.h"


//dimensions of screen are 540*960
void drawLandscape(){
    int i;
    gotoxy(0,GROUND_HEIGHT);

    for (i=0; i<SCREEN_WIDTH; i++){
        printf("%c",196);
    }
}

//ser om skibet overstiger banens gr�nser
int8_t inBounds(SpaceShip_t * p){
//f�lgende er de forskellige tilf�lde den kan overstige gr�nserne

    //hver af returv�rdierne svarer til at frakoble en bestemt tast
    //skibet er for langt til venstre
    if ((*p).x<=0){
        return 1;
   }
    //skibet er for langt til h�jre
    else if ((*p).x>=SCREEN_WIDTH){
        return 2;
    }
    //spilleren fors�ger at grave sig ned i jorden
    else if ((*p).y==GROUND_HEIGHT-1){
        return 3;
    }

    //spilleren flyver ud af banen
    else if ((*p).y>SCREEN_HEIGHT){
       return 4;
    }
    return 0;
}
