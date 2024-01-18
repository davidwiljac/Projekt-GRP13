/*
 * dropperpower.c
 *
 *  Created on: 15 Jan 2024
 *      Author: Bivertical
 */

#include "dropperpower.h"

#define spawnPeriod 1200

/**
  * @brief spawns the dropper
  * @param  gameState: the current state of the game
  * @retval None
  */
void spawndropper(gameState_t* gameState){
	if(runtime-gameState->dropper.lastseentime>=spawnPeriod){
		gameState->dropper.lastseentime=runtime;
		gameState->dropper.isvisible=1;

		// spawns the dropper a specific place in the frame of the game
		position_t spawnPos = {intToFp(4), intToFp(5)*yScale};

		//constant velocity horizontally (y coordinate is locked to 0)
		vector_t vel = {intToFp(1), intToFp(0)*yScale};

		gameState->dropper.position=spawnPos;
		gameState->dropper.nextposition=spawnPos;
		gameState->dropper.velocity=vel;
		gameState->dropper.randomX=-1;

		// gives the dropper when to drop powerups in it's x coordinate randomly
		if(!xValIsValid(gameState->dropper.randomX,6)){
			gameState->dropper.randomX=(rand() % 139);
		}
	}
}

/**
  * @brief updates the droppers position
  * @param  gameState: the current state of the game
  * @retval None
  */
void updatedropper(gameState_t* gameState){
	if(gameState->dropper.isvisible){

		gameState->dropper.nextposition.x=gameState->dropper.position.x+gameState->dropper.velocity.x;
		gameState->dropper.nextposition.y=gameState->dropper.position.y+gameState->dropper.velocity.y;

		// while the dropper is in the game and no powerup is visible then drop a powerup randomly
		while(fpToInt(gameState->dropper.position.x) >= gameState->dropper.randomX && !gameState->powerup.isVisible){

			spawnPowerup(gameState);

		}

		// despawns the dropper when it hits 139 on the x-aksis
		if(fpToInt(gameState->dropper.nextposition.x)>=139){
			deletedropper(fpToInt(gameState->dropper.position.x),fpToInt(gameState->dropper.position.y)/yScale);

			//sets droppers isVisible to 0 to notify that there is none. so the spawnperiod timer can begin
			gameState->dropper.isvisible=0;
			gameState->dropper.lastseentime=runtime;
		}
	}
}

/**
  * @brief redraws the dropper in it's nextposition
  * @param  gameState: the current state of the game
  * @retval None
  */
void conditiondropper(gameState_t* gameState){

	if(gameState->dropper.isvisible){

		//deletes the dropper in it's current position
		deletedropper(fpToInt(gameState->dropper.position.x),fpToInt(gameState->dropper.position.y)/yScale);

		//redraws the dropper in it's nextPosition
		drawdropper(gameState);
	}
	gameState->dropper.position=gameState->dropper.nextposition;
}

/**
  * @brief deletes the dropper
  * @param  takes uint8_t of X- and Y-coordinates
  * @retval None
  */
void deletedropper(uint8_t X,uint8_t Y){
	gotoxy(X,Y);
	printf("       ");
	gotoxy(X,Y-1);
	printf("       ");
	gotoxy(X,Y+1);
	printf("       ");
}


