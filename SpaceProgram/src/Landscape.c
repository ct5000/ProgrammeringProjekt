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


int randomNumber(int32_t mini, int32_t maxi){
    return (rand()%(maxi-mini+1)+mini);
}

void initMineral(mineral_t *p){
    (*p).x=randomNumber(1, 240);
    (*p).y=randomNumber(GROUND_HEIGHT+1, SCREEN_HEIGHT-1) ;
    (*p).fuel=randomNumber(10, 20);


}

void drawMinerals(mineral_t minerals[], int numMinerals){
    int i;

    for (i=0; i < numMinerals;i++){
        fgcolor(1);
        gotoxy((minerals[i]).x,(minerals[i]).y);
        printf("%c",219); //i+49 to show numbers
        fgcolor(0);
    }

}

int8_t createMineral(mineral_t minerals[], int8_t emptyIndex) {
    mineral_t mineral;

            initMineral(&mineral);
            minerals[emptyIndex] = mineral;
            return 1;

}

void groundDraw(){
   int i;
   fgcolor(10);
   bgcolor(3);
    for(i=1; i <=240; i++){
        int r = rand()%20;
        gotoxy(i,56);
        if (r < 18){
            printf("%c",219);
        }
        if (r > 19){
            printf("%c",177);
        }
    }

    for(i=1; i <=240; i++){
        int r = rand()%20;
        gotoxy(i,57);
        if (r < 12){
            printf("%c",219);
        }
        if (r > 16){
            printf("%c",177);
        }
    }
    for(i=1; i <=240; i++){
        int r = rand()%20;
        gotoxy(i,58);
        if (r < 6){
            printf("%c",219);
        }
        if (r > 12){
            printf("%c",177);
        }
    }
    for(i=1; i <=240; i++){
        int r = rand()%20;
        gotoxy(i,59);
        if (r < 2){
            printf("%c",219);
        }
        if (r > 6){
            printf("%c", 177);
        }
    }
    for(i=1; i <=240; i++){
        int r = rand()%20;
        gotoxy(i,60);
        if (r > 4){
            printf("%c",176);
        }
    }
    for(i=1; i <=240; i++){
        int r = rand()%20;
        gotoxy(i,61);
        if (r < 4){
            printf("%c",176);
        }
    }
    bgcolor(6);
    fgcolor(0);
}



