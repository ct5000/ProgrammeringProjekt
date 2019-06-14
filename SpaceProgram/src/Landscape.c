# include "Landscape.h"


//dimensions of screen are 540*960
void drawLandscape(){
    int i;
    gotoxy(0,GROUND_HEIGHT);
    bgcolor(3);

    for (i=0; i<4800; i++){
        printf("%c",176);
    }
    bgcolor(6);
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

int randomNumber(int8_t mini, int8_t maxi){
    return (rand()%(maxi-mini+1)+mini);
}

void initMineral(mineral_t *p){
    (*p).x=randomNumber(1, 239);
    (*p).y=randomNumber(56, 76) ;
    (*p).fuel=randomNumber(10, 20);


}

void drawMinerals(mineral_t minerals[]){
    int i;

    for (i=0; i<3;i++){
        gotoxy((minerals[i]).x,(minerals[i]).y);
        printf("M");
    }
}

