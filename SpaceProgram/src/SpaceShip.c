#include "SpaceShip.h"

/*  Function: initSpaceShip.
* -----------------------------------------------
* initialize the spaceship
*
* *ship; initializes the spaceship.
* x; The vertical start position of the spaceship.
* y; The horizontal start position of the spaceship.
*
*/
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

/*  Function: updateSpaceShip.
* -----------------------------------------------
*   Deletes the spaceship, updates the ships positions inside the map, and draws the spaceship.
*
* *ship; a pointer to the spaceships, that updates its position.
*
*
*/

void updateSpaceShip(SpaceShip_t * ship, boxes_t boxes[]){
    int8_t boundsAfter, boundsBefore;
    int boxIndex;
    deleteAlien((*ship).x,(*ship).y);
    boundsBefore = inBounds(ship, boxes);
    (*ship).x += (*ship).vx;
    (*ship).y += (*ship).vy;
    boundsAfter = inBounds(ship, boxes);
    if (boundsBefore == 3 && boundsAfter == 9) {
            (*ship).x -= (*ship).vx;
            boundsAfter = boundsBefore;
    }



    switch (boundsAfter) {
        case 1: //far left
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
        case 9:
            boxIndex = checkBoxes(ship, boxes, 10);
            (*ship).y = boxes[boxIndex-1].y2 - 2;
           // (*ship).y = boxes[boxIndex-1].y2;
            (*ship).vy = 0;
        default:
            break;
    }
	drawShip((*ship).x, (*ship).y);
}


/*  Function: updateVelocity.
* -----------------------------------------------
* Updates the direction and speed of the spaceship.
*
* *ship; direction of the spaceship.
* key; The pressed char from the user. 'a', 'd', 'w'.
* buffer; An array representing the char show on the lcd.
* place; the area of the spaceship on the map.
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
* *ship; The ships vertical and horizontal placement.
* x; The vertical start position of the spaceship.
* y; The horizontal start position of the spaceship.
*
* returns where the ship is:
* 1; Too far left.
* 2; Too far right.
* 3; on ground height.
* 4; Top.
* 5; Lower left corner.
* 6; Lower right corner.
* 7; Upper left corner.
* 8; Upper right corner.
* 0; None of the above.ww
*/


int8_t inBounds(SpaceShip_t *ship, boxes_t boxes[]){
    int boxIndex = checkBoxes(ship, boxes, 10);

    if ((*ship).x<=1){
        return 1;
    }
    else if ((*ship).x>=SCREEN_WIDTH - 1){
        return 2;
    }
    else if ((*ship).y < 2){
       return 4;
    }
    else if ((*ship).x <= 1 && (*ship).y >= GROUND_HEIGHT - 2) {
        return 5;
    }
    else if ((*ship).x >= SCREEN_WIDTH - 1 && (*ship).y >= GROUND_HEIGHT - 2) {
        return 6;
    }
    else if ((*ship).x <= 1 && (*ship).y <= 2) {
        return 7;
    }
    else if ((*ship).x >= SCREEN_WIDTH - 1 && (*ship).y <= 2) {
        return 8;
    }
    else if (boxIndex){
            if ((*ship).y >= boxes[boxIndex-1].y2-2){
            return 9;
            }
    }
    else if ((*ship).y>=GROUND_HEIGHT - 2){
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

	if ((key == 'e' || key == 'E')  && (place == 3 || place == 9)){ //user presses e and the ship is on the ground.

            i = checkMinerals(ship, minerals, numMinerals);

            if (i){ //The ship is above a mineral

                (*ship).fuel += (minerals[i-1]).fuel;
                (*ship).powerUp += (minerals[i-1]).powerUp;

                for (j = GROUND_HEIGHT; j <= (minerals[i - 1]).y; j++ ){
                    gotoxy((*ship).x, j);
                    printf("%c",186);
                }
                for (j = (minerals[i - 1]).y; j >= GROUND_HEIGHT; j-- ){
                    gotoxy((*ship).x, j);
                    printf("%c",219);
                }

                addfuel(ship,buffer);
                addPowerBullet((*ship).powerUp,buffer);
                return i - 1;

            }
            else { //The ship is not above a mineral.

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
            lcdWriteBar("E", buffer, 0,25+i);
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
void subfuel(SpaceShip_t * ship, uint8_t *buffer, int fuelsub){
        int8_t i;
        for (i=0; i < fuelsub; i++){
            (*ship).fuel--;
            lcdWriteBar(" ", buffer, 0,25+(*ship).fuel);
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
        for (i=1; i<numMinerals; i++){

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

        lcdWriteString("<3", buffer, 1,30+((i*5)*2));

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
        (*ship).lives--;
        lcdWriteString("  ", buffer, 1,30+(((*ship).lives*5)*2));
      //  lcd_write_string(" ", buffer, 1,35+(((*ship).lives*5)*2));
        lcd_push_buffer(buffer);
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

int checkBoxes(SpaceShip_t *ship, boxes_t boxes[], int numBoxes){
    int8_t i;
        for (i=0; i<numBoxes; i++){

            if ((*ship).x + 1 >= (boxes[i]).x1 && (*ship).x - 1 <= (boxes[i]).x2){
            return i+1;
            }
        }
    return 0;
}



