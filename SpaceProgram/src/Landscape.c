# include "Landscape.h"


//dimensions of screen are 540*960
void drawLandscape(){
    int i;
    gotoxy(0,GROUND_HEIGHT);

    for (i=0; i<SCREEN_WIDTH; i++){
        printf("%c",196);
    }
}

//ser om skibet overstiger banens grænser
int8_t inBounds(SpaceShip_t * p){
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
