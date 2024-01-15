#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "types.h"
#include "ansi.h"
#include "bullet.h"
#include "drivers.h"
#include "enemy.h"
#include "nuke.h"
#include "powerup.h"
#include "spaceship.h"
#include "menu.h"
#include "fixedPoint.h"
#include "linkedList.h"
#include "graphics.h"
#include "powerup.h"
#include "sound.h"

#define framePeriod 4 //time in centiseconds deciding how often game frame is redrawn. 4 results in 25 fps

/**
  * @brief  Sets all the relevant variables to reset values
  * @param  gamestate: the current state of the game
  * @retval None
  */
void initVariables(gameState_t* gameState){
	spaceship_t initSpaceship = {{intToFp(3), intToFp(40*yScale)}, //previous position
			{intToFp(3), intToFp(40*yScale)}, //position
			{intToFp(3), intToFp(40*yScale)}, //next Position
			1, 0}; //Number of parts, powerups
	moon_t moon = {70,20*yScale,100};// (x, y, mass)
	
	gameState->enemyLL = NULL;
	gameState->bulletLL = NULL;

	nuke_t* nuke = malloc(sizeof(nuke_t));
	position_t pos = {0,0};
	nuke->position = pos;
	nuke->nextPosition = pos;
	//nuke->velocity = {0,0};
	nuke->isDeployed = 0;
	nuke->readyState = 0;
	gameState->nuke = nuke;
	gameState->nuke->lastDetonationTime = 0xFFFFFFFF;
	gameState->nuke->circleClear = 1;


	gameState->activeScreen=0; //menu screen
	gameState->difficulty=1;   // medium (if changed here, update also definition of diffBtn)
	gameState->btnSelected=0; //start game
	gameState->isDead=0;
	gameState->score=0;
	gameState->cityLives=3;
	gameState->spaceship= initSpaceship;
	gameState->bossMode = 0;
	gameState->moon = moon;
	gameState->powerup.lastUseTime=0;
	gameState->powerup.isVisible=0;
	gameState->enemyCanonDisableTime = 0;
	gameState->enemyCanonsUnchanged =1;

	gameState->soundIndex = 0;
	gameState->soundTime = 0;
	gameState->soundToPlay = 0;
}

void drawOnscreenMessage(gameState_t* gameState){
	if(runtime-gameState->enemyCanonDisableTime <= enemyDisableDuration && !gameState->enemyCanonsUnchanged){
		gotoxy(65,5);
		printf("Enemy canons are disabled");
	} else {
		gotoxy(65,5);
		printf("                         ");
	}
}

/**
  * @brief  draws the current state of the game
  * @param  gamestate: the current state of the game
  * @retval None
  */
void drawScreen(gameState_t* gameState) {

	drawOnscreenMessage(gameState);
	drawSpaceship(gameState);
	drawEnemy(gameState);
	drawBullets(gameState);
	drawPowerup(gameState);
	drawhearth(gameState);
	drawMoon(gameState->moon.x, gameState->moon.y);
	drawNuke(gameState);

}

/**
  * @brief  checks if the player is dead, and writes the score to memory if applicable
  * @param  gamestate: the current state of the game
  * @retval None
  */
void checkIfDead(gameState_t* gameState){

	if(gameState->cityLives == 0){
		gameState->activeScreen = 3;

	}
}

/**
  * @brief  Checks if 'f' is pressed and (de)activates bossKey i it's pressed
  * @param  gamestate: the current state of the game
  * @retval None
  */
void checkBossKey(gameState_t* gameState){
	char c = uart_get_char();
	if(c == 'f'){
		if(gameState->activeScreen != 4){
			clrscr();
			gameState->lastScreen = gameState->activeScreen;
			gameState->activeScreen = 4;
		}else{
			gameState->activeScreen = gameState->lastScreen;
		}
	}
}

/**
  * @brief  The main loop of the game. Runs the menus, if activeScreen == 1 runs the game.
  * @param  None
  * @retval None
  */
int main(void) {
	gameState_t gameState;

	//Defines the menu buttons
	const button_t startBtn = {75,15,"START"};
	const button_t diffBtn = {68,20,"DIFFICULTY: MEDIUM"};
	const button_t helpBtn = {75,25,"HELP"};
	button_t btnList[] = {startBtn, diffBtn, helpBtn}; //always only 3 buttons!

	//Sets up all the used hardware
	uart_init(512000);
	initVariables(&gameState);
	initJoystick();
	initTimer();
	initBuzzerPin();
	initRGB();
	I2C_init();
	analogConfigPorts();
	uint8_t color[] = {0,0,0};
	RGBColor(color);
	srand(readPotentiometer());   //RNG

	while(1){
		switch(gameState.activeScreen){
		case 0: //MENU SCREEN ---------------------------------------------------------------------
			//Sets up the menu
			clrscr();
			drawWindow(0);
			drawbackground(); // stars in background
			drawMoon(gameState.moon.x, gameState.moon.y);
			drawMenuScreen(btnList, &gameState);

			//Continuously checks if the joystick is used and acts accordingly
			while(gameState.activeScreen==0){
				checkBossKey(&gameState);
				if(downIsPressed()){
					drawBtnAsDeselected(btnList[gameState.btnSelected]);
					gameState.btnSelected=(gameState.btnSelected+1)%3;
					drawBtnAsSelected(btnList[gameState.btnSelected]);
				}
				else if(upIsPressed()){
					drawBtnAsDeselected(btnList[gameState.btnSelected]);
					if(gameState.btnSelected==0) gameState.btnSelected=2;
					else gameState.btnSelected=gameState.btnSelected-1;
					drawBtnAsSelected(btnList[gameState.btnSelected]);
				}
				if(centerIsPressed()){
					if(gameState.btnSelected==0){ //START BUTTON
						gameState.activeScreen=1; //Game screen
					}
					else if(gameState.btnSelected==1){ // DIFFICULTY BUTTON
						gameState.difficulty=(gameState.difficulty+1)%3;
						gotoxy(diffBtn.x+15, diffBtn.y+1);
						if(gameState.difficulty==0){
							printf("EASY  ");
						} else if(gameState.difficulty==1){
							printf("MEDIUM");
						} else if(gameState.difficulty==2){
							printf("HARD  ");
						}
					}
					else if(gameState.btnSelected==2){ // HELP BUTTON
						gameState.activeScreen=2;// help screen
					}
				}
			}
			break;
		case 1: // GAME SCREEN -----------------------------------------------------------------------
			//Sets up the game screen
			clrscr();
			uint32_t frameLastUpdated=0;
			gameState.powerup.lastUseTime = runtime;
			drawWindow(1);
			drawMoon(gameState.moon.x, gameState.moon.y);
			drawhearth(&gameState);
			drawCity();

			drawScore(&gameState);
			gameState.powerup.lastUseTime = runtime; //Starts the spawing of powerups
			gameState.nuke->lastActivationTime = runtime; //Start charging of nuke
			gameState.soundTime = runtime; //Starts the soundengine

			gameState.nextEnemySpawn = runtime + 20; //Spawns first enemy after 0.2 seconds

			//Continuously updates the game updateing sound and bosskey as quicly as possible, and the rest 4 times pr second
			while(gameState.activeScreen==1){
				checkBossKey(&gameState);
				playSound(&gameState);
				if(runtime-frameLastUpdated>=framePeriod){//
					spawnEnemy(&gameState);
					spawnPowerup(&gameState);

					updateSpaceship(&gameState);
					updateEnemy(&gameState);
					updatePowerup(&gameState);
					shootSpaceship(&gameState);
					shootEnemy(&gameState);
					updateBullets(&gameState);

					detectBulletHit(&gameState);
					detectCityHit(&gameState);
					updateNuke(&gameState);
					checkIfDead(&gameState);

					drawScreen(&gameState);
					frameLastUpdated=runtime;
				}
		}
			break;
		case 2:// HELP SCREEN ------------------------------------------------------------------------
			//Sets up the help screen
			clrscr();
			drawWindow(0);
			drawbackground(); // stars in background
			drawHelpScreen();

			//If center is pressed leave the help screen
			while(gameState.activeScreen==2){
				checkBossKey(&gameState);
				if(centerIsPressed()){
					gameState.activeScreen=0;//MENU SCREEN
				}
			}
			break;
		case 3:// GAME OVER SCREEN -------------------------------------------------------------------
			//Sets up the game over screen
			clrscr();

			gotoxy(50,5); printf(" _____   ___  ___  ___ _____   _____  _   _ ___________ ");
			gotoxy(50,6); printf("|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\");
			gotoxy(50,7); printf("| |  \\// /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ /");
			gotoxy(50,8); printf("| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    /");
			gotoxy(50,9); printf("| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\ ");
			gotoxy(50,10); printf(" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|");


			gotoxy(64,15);
			printf("SCORE: %d", gameState.score);
			if(gameState.score<=30){
				printf(" (you suck)");
			}

			if(gameState.score>readFromFlash(0x0800F800)){
				gotoxy(64,17);
				printf("NEW HIGHSCORE!");
				writeToFlash(gameState.score, 0x0800F800);
			} else {
				gotoxy(64,17);
				printf("Your highscore is %d", readFromFlash(0x0800F800));
			}

			gotoxy(62,30);
			printf("Press down on joystick to continue");





			while(gameState.activeScreen==3){
				checkBossKey(&gameState);
				if(downIsPressed()){
					initVariables(&gameState);
					gameState.activeScreen=0;//MENU SCREEN
				}
			}
			break;
		case 4: // BOSS KEY --- Draws the bosskey screen and checks if it should leave it again
			drawBossKey();
			while(1){
				checkBossKey(&gameState);
				if(gameState.activeScreen !=4){
					break;
				}
			}
			break;
		}
	}
}
