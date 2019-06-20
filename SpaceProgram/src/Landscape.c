# include "Landscape.h"


//dimensions of screen are 540*960
void drawLandscape(){
    int i;
    gotoxy(0,GROUND_HEIGHT);

    clrscr();
    bgcolor(2+rand()%7);
    fgcolor(2+rand()%15);
    for (i=0; i<SCREEN_WIDTH*12; i++){
        printf("%c",176);
    }

}


int randomNumber(int32_t mini, int32_t maxi){
    return (rand()%(maxi-mini+1)+mini);
}

void initMineral(mineral_t *p){
    int num;
    (*p).x=randomNumber(1, 240);
    (*p).y=randomNumber(GROUND_HEIGHT+1, SCREEN_HEIGHT-10) ;
    (*p).fuel=randomNumber(5, 12);
    num = rand()%2;
    if (num == 1) {
            (*p).powerUp = 1;
    }
    else {
            (*p).powerUp = 0;
    }
}

void drawMinerals(mineral_t minerals[], int numMinerals){
    int i;

    for (i=0; i < numMinerals;i++){
        fgcolor(1);
        gotoxy((minerals[i]).x,(minerals[i]).y);
        printf("%c",219); //i+49 to show numbers
        fgcolor(7);
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
   int color = rand()%17;
   if (color == 1 || color == 0){
    color+=2;
   }

   fgcolor(color);
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
    bgcolor(0);
    fgcolor(7);
}



