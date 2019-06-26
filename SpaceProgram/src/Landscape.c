# include "Landscape.h"

/*  Function: drawlandscape.
 * -----------------------------------------------
 * Draws the landscape at ground height and all the way down to screen height.
 *
 * GROUND_HEIGHT; ground level.
 *
 */
int8_t drawLandscape(int8_t change, int8_t colorBG, int8_t colorFG){
    int i;
    gotoxy(1,GROUND_HEIGHT);
    clrscr();
    if (change){ //checks if the color needs to change
        colorBG = 2+rand()%BGCOLORS_MAX;

    }
    bgcolor(colorBG);
    fgcolor(colorFG);
    for (i=0; i<SCREEN_WIDTH*(SCREEN_HEIGHT-GROUND_HEIGHT+2); i++){ //goes through the lines and draws the landscape
        printf("%c",LANDSCAPE_CHAR);
    }
    bgcolor(BG_STANDARD); //resets background color to black
    return colorBG;
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
    (*mineral).x=randomNumber(1, SCREEN_WIDTH);
    (*mineral).y=randomNumber(GROUND_HEIGHT+1, SCREEN_HEIGHT) ;
    (*mineral).fuel=randomNumber(FUEL_MIN, FUEL_MAX);
    if (num < 4) { //checks if the mineral has a power bullet
            (*mineral).powerUp = 1;
            (*mineral).shield = 0;
    }
    else if (num == 5){ //checks if the mineral has a shield
            (*mineral).shield = 1;
            (*mineral).powerUp = 0;
    }
    else { //mineral has nothing but fuel
            (*mineral).powerUp = 0;
            (*mineral).shield =0;
    }
}

/*  Function: drawMinerals.
 * -----------------------------------------------
 * Draws the minerals at their position.
 *
 * minerals; array of the minerals positions.
 * numMinerals; the amount of minerals.
 *
 * returns; void.
 */
void drawMinerals(mineral_t minerals[], uint8_t numMinerals){
    int i;
    for (i=0; i < numMinerals;i++){
        fgcolor(MINERAL_COLOR);
        gotoxy((minerals[i]).x,(minerals[i]).y);
        printf("%c",MINERAL_CHAR);
        fgcolor(FG_STANDARD);
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
int8_t groundDraw(int8_t change, int8_t colorFG){
    int i;
    int color;
    if (change){ //checks if the foreground color needs to change
        color = rand()%17;
        if (color == 1 || color == 0){
            color+=2;
       }
    }
    else{
        color = colorFG;
    }
    fgcolor(color);
    for(i=1; i <=SCREEN_WIDTH; i++){ //draws top layer of ground
        int r = rand()%GROUND_RANDOM;
        gotoxy(i,GROUND_HEIGHT);
        if (r < 18){
            printf("%c",MINERAL_CHAR);
        }
        if (r > 19){
            printf("%c",GROUND_CHAR);
        }
    }

    for(i=1; i <=SCREEN_WIDTH; i++){ //draws second layer of ground
        int r = rand()%GROUND_RANDOM;
        gotoxy(i,GROUND_HEIGHT+1);
        if (r < 12){
            printf("%c",MINERAL_CHAR);
        }
        if (r > 16){
            printf("%c",GROUND_CHAR);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){ //draws third layer of ground
        int r = rand()%GROUND_RANDOM;
        gotoxy(i,GROUND_HEIGHT+2);
        if (r < 6){
            printf("%c",MINERAL_CHAR);
        }
        if (r > 12){
            printf("%c",GROUND_CHAR);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){ //draws fourth layer of ground
        int r = rand()%GROUND_RANDOM;
        gotoxy(i,GROUND_HEIGHT+3);
        if (r < 2){
            printf("%c",MINERAL_CHAR);
        }
        if (r > 6){
            printf("%c", GROUND_CHAR);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){ //draws fifth layer of ground
        int r = rand()%GROUND_RANDOM;
        gotoxy(i,GROUND_HEIGHT+4);
        if (r > 4){
            printf("%c",GROUND_CHAR);
        }
    }
    for(i=1; i <=SCREEN_WIDTH; i++){ //draws sixth layer of ground
        int r = rand()%GROUND_RANDOM;
        gotoxy(i,GROUND_HEIGHT+5);
        if (r < 4){
            printf("%c",GROUND_CHAR);
        }
    }
    bgcolor(BG_STANDARD);
    fgcolor(FG_STANDARD);
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
    (*box).x2= (*box).x1+rand()%BOX_WIDTH_MAX;
    (*box).y2 = (*box).y1-rand()%BOX_HEIGHT_MAX;
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
void drawBoxes(boxes_t boxes[], int8_t numBoxes, int8_t colorFG){
    int i, j, k;
    fgcolor(colorFG);
    for (i=0; i < numBoxes;i++){ //goes through all boxes and draws them
        for(j=boxes[i].x1; j <= boxes[i].x2; j++){
             for(k=boxes[i].y2; k <= boxes[i].y1; k++){
                drawSymbol(j , k, MINERAL_CHAR);

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

