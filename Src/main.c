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

void initVariables(gameState_t* gameState){
//	gameState->runtime=0;
	gameState->activeScreen=0; //menu screen
	gameState->difficulty=1;   // medium (if changed here, update also definition of diffBtn)
	gameState->btnSelected=0; //start game
	gameState->isDead=0;
	gameState->score=0;
	gameState->cityLives=3;
	gameState->bossMode = 0;
	//TODO: continue to initialize everything
}


void drawScreen(gameState_t* gameState) {
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
	srand(time(NULL));   //RNG


	while(1){
		switch(gameState.activeScreen){
		case 0: //MENU SCREEN ---------------------------------------------------------------------
			clrscr();
			drawBox(1,1,156,43,0);//window
			drawMenuScreen(btnList, &gameState);

			while(gameState.activeScreen==0){

				//Bosskey test
				int bossKeyChange = bossKey(&gameState);
				if(bossKeyChange == 1) continue;
				else if(bossKeyChange == 2){
					//Initialize window agian
					clrscr();
					drawBox(1,1,156,43,0);//window
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
			while(gameState.activeScreen==1){

				//Bosskey test
				int bossKeyChange = bossKey(&gameState);
				if(bossKeyChange == 1) continue;
				else if(bossKeyChange == 2){
					//Initialize window agian
					clrscr();
					printf("GAME SCREEN");
				}
				updateEnemy(&gameState);
			}
			break;
		case 2:// HELP SCREEN ------------------------------------------------------------------------
			clrscr();
			drawBox(1,1,156,43,0);//window
			drawHelpScreen();
			while(gameState.activeScreen==2){
				//Bosskey test
				int bossKeyChange = bossKey(&gameState);
				if(bossKeyChange == 1) continue;
				else if(bossKeyChange == 2){
					//Initialize window agian
					clrscr();
					drawBox(1,1,156,43,0);//window
					drawHelpScreen();
				}

				if(centerIsPressed()){
					gameState.activeScreen=0;//MENU SCREEN
				}
			}
			break;
		case 3:// GAME OVER SCREEN -------------------------------------------------------------------
			clrscr();
			printf("GAME OVER\nYour score is %d", gameState.score);
			while(gameState.activeScreen==3){
				if(bossKey(&gameState)) break;

				if(centerIsPressed()){
					gameState.activeScreen=0;//MENU SCREEN
				}
			}
			break;
		}
	}
}
