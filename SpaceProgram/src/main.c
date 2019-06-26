/*  Main
 * -----------------------------------------------
 * This is the main file for the game Space Rescue.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "stm32f30x_conf.h" //STM32 config
#include "30010_io.h" // Input/output libarary for this course
#include "ansi.h"
#include "mbed.h"
#include "LCD.h"
#include "SpaceShip.h"
#include "Landscape.h"
#include "menu.h"
#include "aliens.h"
#include "Cannon.h"
#include "bossKey.h"

#define MAX_ALIENS 25
#define MAX_BULLETS 5
#define MAX_POWER_BULLETS 2
#define MAX_MINERALS 50
#define BUFFER_SIZE 512
#define TAKE_OFF_FUEL 55
#define START_SPAWN_RATE

/*  Function: setupHardware
 * -----------------------------------------------
 * Setup for all the hardware used in the game
 *
 * buffer:
 *
 * return: void
 */
void setupHardware(uint8_t *buffer) {
    uart_init(960000);
    setTimer();
    startStop();
    setTimer2();
    setFreq(0);
    setupLED();
    setupPot();
    memset(buffer, 0x00, BUFFER_SIZE);
    lcd_init();
    lcd_push_buffer(buffer);
    lcdWriteString("FUEL:",buffer,0,0);
    lcdWriteString("LIVES:",buffer,1,0);
    lcdWriteString("POW B:",buffer,2,0);
    lcd_push_buffer(buffer);
}


int main(void){
    alien_t aliens[MAX_ALIENS];
    int8_t numAliens = 0;
    int8_t killedAliens;
    mineral_t minerals[MAX_MINERALS];
    int8_t numMinerals = 0;
    int8_t mineralIndex;
    boxes_t boxes[NUMBER_BOXES];
    int8_t numBoxes = 0;
    int8_t level=1;
    bullet_t bullets[MAX_BULLETS];
    int8_t numBullets = 0;
    int8_t aliveBullet;
    bullet_t powerBullets[MAX_POWER_BULLETS];
    int8_t numPowerBullets = 0;
    int i;
    int on = 0;
    int endgame = 0;
    int where = 1;
    char key;
    int spawnRate;
    int startSpawnRate;
    int score = 1000;
    int pos;
    int colorFG, colorBG;
    SpaceShip_t skib;
    SpaceShip_t *ship = &skib;
    uint8_t buffer[BUFFER_SIZE];
    setupHardware(buffer);
    color(7,0);
    while(1){
        switch(where){
            case 1:
                startSpawnRate = START_SPAWN_RATE
                spawnRate = startSpawnRate;
                runningMenu();
                srand(getTime()); //new seed for rand() depending on the current time from start of the game.
                resetTime();
                startStop();
                clrscr();
                //drawing the landscape, ground and extra boxes on the screen
                colorBG = drawLandscape(1, colorBG, colorFG);
                colorFG = groundDraw(1, colorFG);
                for (numBoxes = 0; numBoxes < NUMBER_BOXES; numBoxes++) {
                        createBoxes(boxes, numBoxes);
                }
                drawBoxes(boxes, numBoxes, colorFG);
                //initializing the minerals and draws it
                for (numMinerals = 0; numMinerals < MAX_MINERALS; numMinerals++) {
                        createMineral(minerals, numMinerals);
                }
                drawMinerals(minerals, numMinerals);
                initSpaceShip(ship);
                numAliens = 0;
                //setting up the LCD display with the correct fuel and lives
                addfuel(ship,buffer);
                addLives(ship, buffer);
                where = 2;
                break;
            case 2:
                    //subtracts from the spawn rate every 5 seconds
                    if (getSpawnRateFlag() >= 500 && spawnRate > 10){
                            spawnRate--;
                            resetSpawnRateFlag();
                    }
                    if (getAlienFlag() >= 10) { //enters this every minimum 0.1 seconds
                        if (numAliens <= MAX_ALIENS){
                            if(spawnAlien(aliens, numAliens, spawnRate)) { //potentially creates an alien
                                    numAliens++;
                            }
                        }
                        updateAliens(aliens,ship ,numAliens, buffer, boxes); //updates position of aliens
                        if ((*ship).fuel >= TAKE_OFF_FUEL){ //checks if it is enough fuel. If it is the LED starts blinking
                            if (on) {
                                    writeLED(0);
                                    on = 0;
                            }
                            else {
                                    writeLED(2);
                                    on = 1;
                            }
                        }
                        else {
                            writeLED(0);
                        }
                        resetAlienFlag();
                    }
                    if (uart_get_count() > 0) { //reads from the keyboard if a button has been pushed
                        key = uart_get_char();
                        uart_clear();
                    }
                    if (key == 'b') { //checks for bossKey
                            where = 4;
                    }
                    pos = inBounds(ship, boxes);
                    updateVelocity(ship, key, buffer, pos );
                    mineralIndex = drill(ship, key,pos, minerals, numMinerals, buffer);
                    if (mineralIndex) { //if the user has drilled a mineral it will be removed
                            mineralKilled(minerals, mineralIndex, numMinerals);
                            numMinerals--;
                    }
                    //checks if the spaceship has a velocity or is flying and has been at least 0.03 seconds since last time
                    if ( (( ((*ship).vy != 0) || ((*ship).vx != 0) ) || pos == 0) && getShipFlag2() > 3){
                            updateSpaceShip(ship, boxes);
                            if (collide(aliens, ship , numAliens, buffer)) {
                                    numAliens--;
                            }
                            resetShipFlag2();
                    }
                    //checks if a bullet has been fired and which one
                    if (key==' ' && numBullets < 5){
                            createBullet(bullets, numBullets, ship, 0);
                            numBullets++;
                    }
                    else if (key == 'g' && (*ship).powerUp > 0 && numPowerBullets < 3) {
                            createBullet(powerBullets, numPowerBullets, ship, 1);
                            numPowerBullets++;
                            subPowerBullet(ship, buffer, 1);
                    }
                    if (getBulletFlag() >= 8) { //checks it has been at least 0.08 seconds since last time
                            score--;
                            //prints score
                            gotoxy(115,1);
                            printf("%03d", score);
                            for (i=0; i<numBullets; i++){ //updates positions of normal bullets and check if they git aliens
                                    aliveBullet = updateBulletPosition(&bullets[i], boxes);
                                    killedAliens = hitAliens(aliens, bullets, numAliens, numBullets);
                                    numAliens -= killedAliens;
                                    if (killedAliens) {
                                            score += 50;
                                    }
                                    if((!aliveBullet) || killedAliens) {
                                            bulletKilled(bullets, i, numBullets);
                                            numBullets--;
                                    }
                            }
                            for (i=0; i< numPowerBullets; i++){ //updates positions of powerBullets and check if they git aliens
                                    aliveBullet = updateBulletPosition(&powerBullets[i], boxes);
                                    killedAliens = hitAliens(aliens, powerBullets, numAliens, numPowerBullets);
                                    numAliens -= killedAliens;
                                    if (killedAliens) {
                                            score += 50;
                                    }
                                    if(!aliveBullet) {
                                            bulletKilled(powerBullets, i, numPowerBullets);
                                            numPowerBullets--;
                                    }
                            }
                            resetBulletFlag();
                    }
                    endgame = endGameCondition(ship, minerals,numMinerals, score); //check end conditions for the level
                    if (endgame == 2 || endgame == 3 || score == 0){ //the player lost
                            where = 3;
                    } //if the player got to next level
                    else if (endgame == 1){
                            where = 5;
                    }
                    key = 0x0D;
                    break;
            case 3:
                    //runs game over screen and resets the value to start value
                    gameOver(endgame, score, level);
                    where = 1;
                    score = 1000;
                    numBullets=0;
                    numPowerBullets=0;
                    subfuel(ship, buffer,(*ship).fuel);
                    subPowerBullet(ship,buffer, (*ship).powerUp);
                    break;
            case 4:
                    //bossKey screen and draws the landscape again after it is over
                    bossKey();
                    clrscr();
                    drawLandscape(0, colorBG, colorFG);
                    groundDraw(0, colorFG);
                    drawMinerals(minerals, numMinerals);
                    drawBoxes(boxes, numBoxes, colorFG);
                    drawShip((*ship).x, (*ship).y, 0);
                    where = 2;
                    fgcolor(7);
                    break;
            case 5:
                    //next level screen with higher score
                    nextLevel(score, level);
                    score += 1000;
                    if (startSpawnRate >= 15){ //increases the start spawn rate of a level when it is 15 or more
                        startSpawnRate -= 5;
                    }
                    spawnRate = startSpawnRate;
                    //draws new landscape, ground and boxes
                    colorBG = drawLandscape(1, colorBG, colorFG);
                    colorFG = groundDraw(1, colorFG);
                    for (numBoxes = 0; numBoxes < NUMBER_BOXES; numBoxes++) {
                        createBoxes(boxes, numBoxes);
                    }
                    drawBoxes(boxes, numBoxes, colorFG);
                    resetTime();
                    startStop();
                    shipNextLevel(ship, buffer); //updates the ship for the next level
                    //resets values for minerals, aliens and bullets
                    numMinerals =0;
                    numAliens =0;
                    numBullets = 0;
                    numPowerBullets =0;
                    //initializes minerals and draws them
                    for (numMinerals = 0; numMinerals < MAX_MINERALS-level*3; numMinerals++) {
                        createMineral(minerals, numMinerals);
                    }
                    drawMinerals(minerals, numMinerals);
                    level++;
                    where = 2;
                    break;
        }
    }
}
