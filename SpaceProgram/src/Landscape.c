# include "Landscape.h"


//dimensions of screen are 540*960
void drawLandscape(){
    int i;
    gotoxy(0,GROUND_HEIGHT);

    bgcolor(6);
    clrscr();
    bgcolor(3);
    for (i=0; i<SCREEN_WIDTH*12; i++){
        printf("%c",176);
    }
    bgcolor(6);
}

//ser om skibet overstiger banens grænser


int randomNumber(int8_t mini, int8_t maxi){
    return (rand()%(maxi-mini+1)+mini);
}

void initMineral(mineral_t *p){
    (*p).x=randomNumber(1, SCREEN_WIDTH-1);
    (*p).y=randomNumber(GROUND_HEIGHT+1, SCREEN_HEIGHT-1) ;
    (*p).fuel=randomNumber(10, 20);


}

void drawMinerals(mineral_t minerals[]){
    int i;

    for (i=0; i < 3;i++){
        fgcolor(1);
        gotoxy((minerals[i]).x,(minerals[i]).y);
        printf("%c",i+49);
        fgcolor(0);
    }

}

