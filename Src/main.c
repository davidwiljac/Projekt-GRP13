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

void initVariables(gameState_t* gameState){
	gameState->activeScreen=0; //menu screen
	gameState->difficulty=1;   // medium
	gameState->menuSelected=0; //start game
	gameState->isDead=0;
	gameState->score=0;
	gameState->cityLives=3;
	//TODO: continue to initialize everything
}


void cycleDifficulty(gameState_t* gameState) {
	if(gameState->difficulty>=2){
		gameState->difficulty=0;
	} else {
		gameState->difficulty++;
	}
}
void drawScreen(gameState_t* gameState) {}
void bossKey(gameState_t* gameState){}

int main(void)
{
	while(1){}
}
