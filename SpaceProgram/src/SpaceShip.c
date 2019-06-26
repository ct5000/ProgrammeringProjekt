#include "SpaceShip.h"

/*  Function: initSpaceShip.
 * -----------------------------------------------
 * initialize the spaceship
 *
 * ship: initializes the spaceship
 *
 * return: void
 */
void initSpaceShip(SpaceShip_t *ship) {
    (*ship).x=randomNumber(60, 180);
    (*ship).y=START_Y;
    (*ship).vx = 0;
    (*ship).vy = 0;
    (*ship).lives = START_LIVES;
    (*ship).fuel=START_FUEL;
    (*ship).powerUp = 0;
    (*ship).shield = 0;
    drawShip((*ship).x,(*ship).y,(*ship).shield);
}

/*  Function: shipNextLevel
 * -----------------------------------------------
 * Updates spaceship for the next level
 *
 * ship: initializes the spaceship.
 * buffer: buffer for the LCD display
 *
 * return: void
 */
void shipNextLevel(SpaceShip_t *ship, uint8_t *buffer) {
    subfuel(ship, buffer, (*ship).fuel);
    (*ship).x=randomNumber(60, 180);
    (*ship).y=START_Y;
    (*ship).vx=0;
    (*ship).vy=0;
    (*ship).fuel = START_FUEL;
    drawShip((*ship).x,(*ship).y,(*ship).shield);
    addfuel(ship,buffer);
}

/*  Function: updateSpaceShip.
 * -----------------------------------------------
 *   Deletes the spaceship, updates the ships positions inside the map, and draws the spaceship.
 *
 * ship: a pointer to the spaceships, that updates its position.
 *
 * return: void
 */

void updateSpaceShip(SpaceShip_t * ship, boxes_t boxes[]){
    int8_t boundsAfter, boundsBefore;
    int8_t boxIndexBefore, boxIndexAfter;
    int boxIndex;
    deleteAlien((*ship).x,(*ship).y);
    //check bounds and box before update
    boundsBefore = inBounds(ship, boxes);
    boxIndexBefore = checkBoxes((*ship).x, boxes, 10);
    //update position
    (*ship).x += (*ship).vx;
    (*ship).y += (*ship).vy;
    //check bounds after update
    boundsAfter = inBounds(ship, boxes);
    boxIndexAfter = checkBoxes((*ship).x, boxes, 10);
    //if the bounds after is at box and it wasn't before stop the shi
    if ((boundsBefore == 3 || boundsBefore == 0)  && boundsAfter == 9) {
            (*ship).x -= (*ship).vx;
            boundsAfter = boundsBefore;
    } //if different boxes and the new box is higher the ship stops
    else if(boundsAfter == 9 && boxIndexBefore != boxIndexAfter) {
            if (boxes[boxIndexAfter-1].y2 < boxes[boxIndexBefore-1].y2) {
                    (*ship).x -= (*ship).vx;
            }
    }
    switch (boundsAfter) {
        case 1: //too far left
            (*ship).x = SPACESHIP_BORDER;
            (*ship).vx = 0;
            break;
        case 2: //too far right
            (*ship).x = SCREEN_WIDTH - SPACESHIP_BORDER;
            (*ship).vx = 0;
            break;
        case 3: //at ground hight
            (*ship).y = GROUND_HEIGHT - SPACESHIP_BORDER;
            (*ship).vy = 0;
            break;
        case 4: //at top of screen
            (*ship).y = SPACESHIP_BORDER;
            (*ship).vy = 0;
            break;
        case 5: //bottom left corner
            (*ship).y = GROUND_HEIGHT - SPACESHIP_BORDER;
            (*ship).vy = 0;
            (*ship).x = SPACESHIP_BORDER;
            (*ship).vx = 0;
            break;
        case 6: //bottom right corner
            (*ship).y = GROUND_HEIGHT - SPACESHIP_BORDER;
            (*ship).vy = 0;
            (*ship).x = SCREEN_WIDTH - SPACESHIP_BORDER;
            (*ship).vx = 0;
            break;
        case 7: //top left corner
            (*ship).y = SPACESHIP_BORDER;
            (*ship).vy = 0;
            (*ship).x = SPACESHIP_BORDER;
            (*ship).vx = 0;
            break;
        case 8: //top right corner
            (*ship).y = SPACESHIP_BORDER;
            (*ship).vy = 0;
            (*ship).x = SCREEN_WIDTH - SPACESHIP_BORDER;
            (*ship).vx = 0;
            break;
        case 9: //on an box
            boxIndex = checkBoxes((*ship).x, boxes, NUMBER_BOXES);
            (*ship).y = boxes[boxIndex-1].y2 - SPACESHIP_BORDER;
            (*ship).vy = 0;
            break;
        default:
            break;
    }
	drawShip((*ship).x, (*ship).y, (*ship).shield);
}


/*  Function: updateVelocity.
 * -----------------------------------------------
 * Updates the direction and speed of the spaceship.
 *
 * *ship: direction of the spaceship.
 * key: The pressed char from the user. 'a', 'd', 'w'.
 * buffer: An array representing the char show on the lcd.
 * place: the area of the spaceship on the map.
 *
 * return: void
 */

void updateVelocity(SpaceShip_t * ship, char key, uint8_t *buffer, int place) {

    if (key == 'a' && (*ship).fuel>0 && place == 3 && ((*ship).vx > -3)){ //drives left
            (*ship).vx -= 1;
            subfuel(ship, buffer, 1);
    }
    else if (key == 'd' && (*ship).fuel>0 && place == 3 && ((*ship).vx < 3)){ //drives right
            (*ship).vx += 1;
            subfuel(ship, buffer, 1);
    }
    else if (key == 'a' && (*ship).fuel>0 && (!(place == 3) || !(place == 9)) && ((*ship).vx > -3)){ //glides left
            (*ship).vx -= 1;
    }
    else if (key == 'd' && (*ship).fuel>0 && (!(place == 3) || !(place == 9)) && ((*ship).vx < 3)){ //glides right
            (*ship).vx += 1;
    }
    else if (key == 'w' && (*ship).fuel>0 && ((*ship).vy > -2)){ //flies up
            (*ship).vy -= 1;
            subfuel(ship, buffer, 1);
    }
    else if (place == 3 || place == 9){   //stands still
        (*ship).vx = 0;
        (*ship).vy =0;
    }
    else if (getShipFlag1() > 60) { //falls down
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

/*  Function: inBounds.
 * -----------------------------------------------
 * Checks where the spaceship is on the map.
 *
 * ship: The ships vertical and horizontal placement.
 * x: The vertical start position of the spaceship.
 * y: The horizontal start position of the spaceship.
 *
 * returns where the ship is:
 * 1: Too far left.
 * 2: Too far right.
 * 3: on ground height.
 * 4: Top.
 * 5: Lower left corner.
 * 6: Lower right corner.
 * 7: Upper left corner.
 * 8: Upper right corner.
 * 9: Over a box
 * 0: None of the above.
 *
 * return void
 */
int8_t inBounds(SpaceShip_t *ship, boxes_t boxes[]){
    int boxIndex = checkBoxes((*ship).x, boxes, NUMBER_BOXES);
    //too far bottom left
    if ((*ship).x <= SPACESHIP_BORDER && (*ship).y >= GROUND_HEIGHT - SPACESHIP_BORDER) {
        return 5;
    }//too far bottom right
    else if ((*ship).x >= SCREEN_WIDTH - SPACESHIP_BORDER && (*ship).y >= GROUND_HEIGHT - SPACESHIP_BORDER) {
        return 6;
    }//too far upper left
    else if ((*ship).x <= SPACESHIP_BORDER && (*ship).y <= SPACESHIP_BORDER) {
        return 7;
    }//too far upper right
    else if ((*ship).x >= SCREEN_WIDTH - SPACESHIP_BORDER && (*ship).y <= SPACESHIP_BORDER) {
        return 8;
    }//too far left
    else if ((*ship).x<=SPACESHIP_BORDER){
        return 1;
    }//too far right
    else if ((*ship).x>=SCREEN_WIDTH - SPACESHIP_BORDER){
        return 2;
    }//too far up
    else if ((*ship).y < SPACESHIP_BORDER){
       return 4;
    }//over a box
    else if (boxIndex){
            if ((*ship).y >= boxes[boxIndex-1].y2-SPACESHIP_BORDER){
            return 9;
            }
    }//at ground height
    else if ((*ship).y>=GROUND_HEIGHT - SPACESHIP_BORDER){
        return 3;
    }
    return 0;
}

/*  Function: drill.
 * -----------------------------------------------
 * Checks if there is a mineral under the ship, drills down from the ship, either to the placement of a mineral or top screen height.
 * Updates the fuel and powerUp's of the spaceship, Prints it on the lcd.
 *
 * *ship; placement of the ship, fuel level and powerUps.
 * key; The pressed char from the user. 'e', 'E'.
 * buffer; An array representing the char show on the lcd.
 * place; the area of the spaceship on the map.
 * nuMinerals; the number on minerals on the map.
 *
 * returns:
 * 1-i; The drilled mineral.
 * 0; If no mineral is drilled.
 */
int8_t drill(SpaceShip_t * ship, char key, int8_t place, mineral_t minerals[], int numMinerals, uint8_t *buffer){
	int i;
	int j;
	int newFuel;
	if ((key == 'e' || key == 'E')  && (place == 3 || place == 9)){ //user presses e and the ship is on the ground.
            i = checkMinerals(ship, minerals, numMinerals);
            if (i){ //The ship is above a mineral
                //adds fuel if below max
                newFuel=(*ship).fuel + (minerals[i-1]).fuel;
                (*ship).fuel = (newFuel <MAX_FUEL) ? newFuel : MAX_FUEL;
                (*ship).powerUp += (minerals[i-1]).powerUp; //add powerBullet
                if((minerals[i-1]).shield){ //if no shield add a shield
                        (*ship).shield = 1;
                }
                for (j = (*ship).y+SPACESHIP_BORDER; j <= (minerals[i - 1]).y; j++ ){ //graphic drill
                    gotoxy((*ship).x, j);
                    printf("%c",DRILL_CHAR);
                }
                //Update LCD display
                addfuel(ship,buffer);
                addPowerBullet(ship,buffer);
                return i - 1;
            }
            else { //The ship is not above a mineral.

                for (j = 0; j <= SCREEN_HEIGHT; j++ ){ //graphic drill
                    gotoxy((*ship).x, (*ship).y+SPACESHIP_BORDER+j);
                    printf("%c",DRILL_CHAR);
                }
            }
	}
	return 0;
}

/*  Function: addFuel.
 * -----------------------------------------------
 * Writes the fuel bar on the lcd.
 *
 * *ship; fuel level.
 * buffer; An array representing the char show on the lcd.
 */
void addfuel(SpaceShip_t * ship, uint8_t *buffer){
    int8_t i;
        for(i=0; i < (*ship).fuel; i++){
            lcdWriteBar(1, buffer, 0,LCD_START_WRITE+i);
            lcd_push_buffer(buffer);
        }
}

/*  Function: subFuel.
 * -----------------------------------------------
 * deletes the fuel bar on the lcd.
 *
 * *ship; fuel level.
 * buffer; An array representing the char show on the lcd.
 * fuelsub; The amount of used fuel.
 */
void subfuel(SpaceShip_t *ship, uint8_t *buffer, int fuelsub){
        int8_t i;
        for (i=0; i < fuelsub; i++){
            (*ship).fuel--;
            lcdWriteBar(0, buffer, 0,LCD_START_WRITE+(*ship).fuel);
            lcd_push_buffer(buffer);
        }
}

/*  Function: checksMineral.
 * -----------------------------------------------
 * Checks if there is an mineral under the spaceship.
 *
 * *ship; ships horizontal placement.
 * minerals; minerals horizontal placement.
 * numMinerals; number of minerals.
 *
 * returns:
 * i; Which mineral the spaceship is above.
 * 0; If there is not any minerals under the spaceship.
 */
int checkMinerals(SpaceShip_t *ship, mineral_t minerals[], int numMinerals){
    int8_t i;
        for (i=1; i<=numMinerals + 1; i++){
            if ((*ship).x == (minerals[i - 1]).x){
                return i;
            }
        }
    return 0;
}

/*  Function: addLives.
 * -----------------------------------------------
 * Writes a heart for every for the ships lives.
 *
 * *ship; ships lives.
 * buffer; An array representing the char show on the lcd.
 *
 */
void addLives(SpaceShip_t * ship, uint8_t *buffer){
    int i;
        for(i=0; i < (*ship).lives; i++){
            lcdWriteString("<3", buffer, 1,LCD_START_WRITE+((i*LETTER_WIDTH)*2));
            lcd_push_buffer(buffer);
        }
}

/*  Function: subLives.
 * -----------------------------------------------
 * Subtracts a life form the spaceship and the lcd.
 *
 * *ship; ships lives.
 * buffer; An array representing the char show on the lcd.
 *
 * return; void.
 */
void subLives(SpaceShip_t * ship, uint8_t *buffer){
        resetSoundFlag();
        setFreq(500); //starts sound
        (*ship).lives--;
        lcdWriteString("  ", buffer, 1,LCD_START_WRITE+(((*ship).lives*LETTER_WIDTH)*2));
        lcd_push_buffer(buffer);
        while(getSoundFlag() < 40){} //wait for 0.4 seconds
        setFreq(0); //stop sounds

}

/*  Function: endGameCondition.
 * -----------------------------------------------
 * Check if the game is over or won.
 *
 * *ship; a pointer to the ships fuel, lives a vertical position.
 * minerals[]; an array of the minerals.
 * score; The score.
 *
 * return:
 * 1; The ship made it out of the map.
 * 2; The fuel is 0, and there are no minerals under the ship.
 * 3; The ship has no more lives.
 * 0; none of the above.
 */
int8_t endGameCondition(SpaceShip_t *ship, mineral_t minerals[], int numMinerals, int score){
    if ((*ship).y < 3 && (*ship).fuel > 50){
            return 1;
    }
    else if ((*ship).fuel <= 0 &&  (checkMinerals(ship, minerals, numMinerals) == 0)){
            return 2;
    }
    else if ((*ship).lives == 0){
            return 3;
    }
    else if (score == 0){
            return 4;
    }
    return 0;
}

/*  Function: checkBoxes
 * -----------------------------------------------
 * Checks whether there is a box at the x-coordinate. If more boxes it takes the tallest
 *
 * x: x-coordinate to check for boxes
 * boxes: an array of boxes
 * numBoxes: number of boxes in the array
 *
 * return: void

 */
int checkBoxes(int x, boxes_t boxes[], int numBoxes){
    int8_t i;
    int8_t foundBoxes[numBoxes];
    int8_t foundBoxesTotal = 0;
    int8_t largestYIndex;
    for (i=0; i<numBoxes; i++){
        if (x + 1 >= (boxes[i]).x1 && x - 1 <= (boxes[i]).x2){
            foundBoxes[foundBoxesTotal] = i;
            foundBoxesTotal++;
        }
    }
    if (foundBoxesTotal > 0) {
        largestYIndex = foundBoxes[0];
        for (i = 1; i < foundBoxesTotal; i++) {
                if (boxes[foundBoxes[i]].y2 < boxes[largestYIndex].y2) {
                        largestYIndex = foundBoxes[i];
                }
        }
        return largestYIndex + 1;
    }
    else {
        return 0;
    }
}

/* Function: addPowerBullet
 * ---------------------------
 * This function is used update the LCD display when a new power bullet is found.
 * An 'O' is added for every powerBullet on line 3.
 *
 * numPowerBullets: the total number of power bullets
 * buffer: an 512 long array where every element represents a character on LCD display
 *
 * return void
 */
void addPowerBullet(SpaceShip_t * ship, uint8_t *buffer){
    int i;
        for(i=0; i < (*ship).powerUp; i++){ //goes for number of powerUps
            lcdWriteString("O", buffer, 2,LCD_START_WRITE+i*LETTER_WIDTH);
            lcd_push_buffer(buffer);
        }
}

/*Function: subPowerBullet
Keeps the amount of power bullets updated when one is used.
The LCD display is updated to show the correct number of power bullets.

ship: a pointer to the active spaceship. It is used to get the number of power ups.
buffer: an 512 long array where every element represents a character on LCD display

return:void
*/
void subPowerBullet(SpaceShip_t * ship, uint8_t *buffer, int8_t usedPowerUp){
        int8_t i;
        for (i=0; i<usedPowerUp; i++){ //goes for the number of powerUps used
            (*ship).powerUp--;
            lcdWriteString(" ", buffer, 2,LCD_START_WRITE+(*ship).powerUp*LETTER_WIDTH);
            lcd_push_buffer(buffer);
        }

}
