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
#include "MoonGravity.h"

#define framePeriod 4 //time in centiseconds deciding how often game frame is redrawn. 4 results in 25 fps

void initVariables(gameState_t* gameState){
	spaceship_t initSpaceship = {{intToFp(2), intToFp(42)}, {intToFp(2), intToFp(42)}, 1, 20, 0};

	enemyNode_t* node = malloc(sizeof(enemyNode_t));
	enemy_t* enemy = malloc(sizeof(enemy_t));
	position_t* pos = malloc(sizeof(position_t));

	node->enemy = enemy;
	pos->x = 0;
	enemy->position = pos;
	node->enemy = enemy;
	node->nextEnemyNode = 0;
	gameState->enemyLL = node;

	gameState->bulletHead = NULL;

	gameState->activeScreen=0; //menu screen
	gameState->difficulty=1;   // medium (if changed here, update also definition of diffBtn)
	gameState->btnSelected=0; //start game
	gameState->isDead=0;
	gameState->score=0;
	gameState->cityLives=3;
	gameState->spaceship= initSpaceship;
	gameState->bossMode = 0;
	//TODO: continue to initialize everything
}


void drawScreen(gameState_t* gameState) {
	gotoxy(fpToInt(gameState->spaceship.position.x),fpToInt(gameState->spaceship.position.y));
	printf(" ");
	gotoxy(fpToInt(gameState->spaceship.nextPosition.x),fpToInt(gameState->spaceship.nextPosition.y));
	printf("A");
	gameState->spaceship.position=gameState->spaceship.nextPosition;
	drawEnemy(gameState);
	drawBullets(gameState);

	drawhearth(gameState);
	drawMoon(51,17); // moon graphics
}

int8_t bossKey(gameState_t* gameState){
	char c = uart_get_char();
	if(c == 'f'){
		if(gameState->bossMode == 0){
			clrscr();
			gameState->bossMode = 1;
		}else{
			gameState->bossMode = 0;
			return 2;
		}
	}

	if(gameState->bossMode == 1){
		gotoxy(0,0);
		printf("Noget meget vigtigt!");
		return 1;
	}
	return 0;
	uart_clear();
}

void checkIfDead(gameState_t* gameState){
	if(gameState->cityLives == 0){
		gameState->activeScreen = 3;
	}
}

int main(void) {
	gameState_t gameState;
	const button_t startBtn = {75,15,"START"};
	const button_t diffBtn = {68,20,"DIFFICULTY: MEDIUM"};
	const button_t helpBtn = {75,25,"HELP"};
	button_t btnList[] = {startBtn, diffBtn, helpBtn}; //always only 3 buttons!

	uart_init(256000);
	initVariables(&gameState);
	initTimer();
	initJoystick();
	I2C_init();
	srand(time(NULL));   //RNG



	while(1){
		switch(gameState.activeScreen){
		case 0: //MENU SCREEN ---------------------------------------------------------------------
			clrscr();
			drawWindow();
			drawBox(1,1,156,43,0);//window
			drawbackground(); // stars in background
			drawMenuScreen(btnList, &gameState);


			while(gameState.activeScreen==0){
				gotoxy(20,20);
				uint8_t x = I2C_Read(0x98, 0x98, NULL, 1);
				printf("%d\n", x);
				//Bosskey test
				int bossKeyChange = bossKey(&gameState);
				if(bossKeyChange == 1) continue;
				else if(bossKeyChange == 2){
					//Initialize window agian
					clrscr();
					drawBox(1,1,156,43,0);//window
					drawbackground(); // stars in background
					drawMenuScreen(btnList, &gameState);
				}

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
			clrscr();
			printf("GAME SCREEN");
			uint32_t frameLastUpdated=0;
			uint8_t dir = 0;
			gameState.spaceship.lastShotTime=runtime;
			drawbackground(); // stars in background
			drawMoon(51,17);
//			applyGravity(bullet *bullet, drawMoon *drawMoon);
			while(gameState.activeScreen==1){
				//Bosskey test
				int bossKeyChange = bossKey(&gameState);
				if(bossKeyChange == 1) continue;
				else if(bossKeyChange == 2){
					//Initialize window agian
					clrscr();
					gotoxy(0,0);
					printf("GAME SCREEN");
				}

				if(runtime-frameLastUpdated>=framePeriod){//
					updateSpaceship(&gameState, &dir);
					spawnEnemy(&gameState);
					updateEnemy(&gameState);
					shootSpaceship(&gameState);
//					shootEnemy(&gameState);
					updateBullets(&gameState);
					detectBulletHit(&gameState);
					detectCityHit(&gameState);
//					powerUp(&gameState);
//					nukeUpdate(&gameState);
					checkIfDead(&gameState);
					drawScreen(&gameState);
					frameLastUpdated=runtime;
				}
		}
			break;
		case 2:// HELP SCREEN ------------------------------------------------------------------------
			clrscr();
			drawWindow();
			drawBox(1,1,156,43,0);//window
			drawbackground(); // stars in background
			drawHelpScreen();
			while(gameState.activeScreen==2){
				//Bosskey test
				int bossKeyChange = bossKey(&gameState);
				if(bossKeyChange == 1) continue;
				else if(bossKeyChange == 2){
					//Initialize window agian
					clrscr();
					drawBox(1,1,156,43,0);//window
					drawbackground(); // stars in background
					drawHelpScreen();
				}

				if(centerIsPressed()){
					gameState.activeScreen=0;//MENU SCREEN
				}
			}
			break;
		case 3:// GAME OVER SCREEN -------------------------------------------------------------------
			clrscr();
			printf("YOU HELLA DEAD!\n YOU SUCK Your score is %d", gameState.score);
			while(gameState.activeScreen==3){
				//Bosskey test
				int bossKeyChange = bossKey(&gameState);
				if(bossKeyChange == 1) continue;
				else if(bossKeyChange == 2){
					//Initialize window agian
					clrscr();
					printf("YOU HELLA DEAD!\n YOU SUCK Your score is %d", gameState.score);
				}
				if(centerIsPressed()){
					initVariables(&gameState);
					gameState.activeScreen=0;//MENU SCREEN
				}
			}
			break;
		}
	}
}
