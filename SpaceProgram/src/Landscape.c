# include "Landscape.h"

/*  Function: drawlandscape.
* -----------------------------------------------
* Draws the landscape at ground height and all the way down to screen height.
*
* GROUND_HEIGHT; ground level.
*
*/
void drawLandscape(){
    int i;
    gotoxy(1,GROUND_HEIGHT);

    clrscr();
    bgcolor(2+rand()%7);
    fgcolor(2+rand()%15);
    for (i=0; i<SCREEN_WIDTH*(SCREEN_HEIGHT-GROUND_HEIGHT+2); i++){
        printf("%c",176);
    }

}

/*  Function: randomNumber.
* -----------------------------------------------
* Makes a random number between two numbers
*
* mini; minimum random number.
* maxi; max random number.
*
* returns: int random number.
*/
int randomNumber(int32_t mini, int32_t maxi){
    return (rand()%(maxi-mini+1)+mini);
}

/*  Function: initMineral.
* -----------------------------------------------
* Creates minerals at random positions.
*
* mineral; initializes the minerals.
*
* returns; void.
*/
void initMineral(mineral_t *mineral){
    int num = rand()%10;
    (*mineral).x=randomNumber(1, 240);
    (*mineral).y=randomNumber(GROUND_HEIGHT+1, SCREEN_HEIGHT) ;
    (*mineral).fuel=randomNumber(5, 12);

    if (num < 4) {
            (*mineral).powerUp = 1;
    }
    else if (num == 5){
            (*mineral).shield = 1;
    }
    else {
            (*mineral).powerUp = 0;
            (*mineral).shield =0;
    }
}

/*  Function: drawMinerals.
* -----------------------------------------------
* Draws the minerals at their position.
*
* minerals[]; arrat of the minerals positions.
* numMinerals; the amount of minerals.
*
* returns; void.
*/
void drawMinerals(mineral_t minerals[], int numMinerals){
    int i;

    for (i=0; i < numMinerals;i++){
        fgcolor(1);
        gotoxy((minerals[i]).x,(minerals[i]).y);
        printf("%c",219);
        fgcolor(7);
    }
}

/*  Function: initMineral.
* -----------------------------------------------
* Creates minerals in the array.
*
* minerals[]; minerals array.
* emptyIndex;
*
* returns; void.
*/
void createMineral(mineral_t minerals[], int8_t emptyIndex) {
    mineral_t mineral;
    initMineral(&mineral);
    minerals[emptyIndex] = mineral;
}


/*  Function: groundDraw.
* -----------------------------------------------
* Draws random colors on the ground.
*
* returns; void.
*/
int8_t groundDraw(){
   int i;
   int color = rand()%17;
   if (color == 1 || color == 0){
    color+=2;
   }

   fgcolor(color);
    for(i=1; i <=SCREEN_WIDTH; i++){
        int r = rand()%20;
        gotoxy(i,56);
        if (r < 18){
            printf("%c",219);
        }
        if (r > 19){
            printf("%c",177);
        }
    }

    for(i=1; i <=SCREEN_WIDTH; i++){
        int r = rand()%20;
        gotoxy(i,57);
        if (r < 12){
            printf("%c",219);
        }
        if (r > 16){
            printf("%c",177);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){
        int r = rand()%20;
        gotoxy(i,58);
        if (r < 6){
            printf("%c",219);
        }
        if (r > 12){
            printf("%c",177);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){
        int r = rand()%20;
        gotoxy(i,59);
        if (r < 2){
            printf("%c",219);
        }
        if (r > 6){
            printf("%c", 177);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){
        int r = rand()%20;
        gotoxy(i,60);
        if (r > 4){
            printf("%c",176);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){
        int r = rand()%20;
        gotoxy(i,61);
        if (r < 4){
            printf("%c",176);
        }
    }
    bgcolor(0);
    fgcolor(7);
    return color;
}

/*  Function: initBoxes.
* -----------------------------------------------
* Creates boxes at random positions.
*
* box; initializes the box.
*
* returns; void.
*/
void initBoxes(boxes_t *box){
    (*box).x1=randomNumber(1, SCREEN_WIDTH);
    (*box).y1 = GROUND_HEIGHT-1;
    (*box).x2= (*box).x1+rand()%3+30;
    (*box).y2 = (*box).y1-rand()%3;
}


/*  Function: createBoxes.
* -----------------------------------------------
* Create minerals in the array.
*
* boxes[]; the array of boxes.
* emptyIndex;
*
* return; void.
*/
void createBoxes(boxes_t boxes[], int8_t emptyIndex) {
    boxes_t box;
    initBoxes(&box);
    boxes[emptyIndex] = box;
}

/*  Function: drawBoxes.
* -----------------------------------------------
* draws boxes on the surface.
*
* boxes[]; the array of boxes.
* numBoxes; number of boxes.
*
* return; void.
*/
void drawBoxes(boxes_t boxes[], int numBoxes){
    int i, j, k;
    fgcolor(groundDraw());
    for (i=0; i < numBoxes;i++){
        for(j=boxes[i].x1; j <= boxes[i].x2; j++){
             for(k=boxes[i].y2; k <= boxes[i].y1; k++){
                drawSymbol(j , k, 219);

            }
        }
    }
    fgcolor(0);
}


/*  Function: MineralKilled.
* -----------------------------------------------
* Deletes a used mineral.
*
* minerals[]; the array of minerals.
* index; Which mineral is used.
* numMinerals; number of minerals.
*
*/
void mineralKilled(mineral_t minerals[], int8_t index, int8_t numMinerals) {
    int i;
    for (i = index; i < numMinerals - 1; i++) {
        minerals[i] = minerals[i + 1];
    }
}

