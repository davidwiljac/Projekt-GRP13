/*
 * powerup.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "powerup.h"

#define spawnPeriod 1000
/**
  * @brief  Checks if it should spawn a powerup and does if it should
  * @param  gameState: the current state of the game
  * @retval None
  */
void spawnPowerup(gameState_t* gameState){
	if(runtime-gameState->powerup.lastUseTime>=spawnPeriod){
		gameState->powerup.lastUseTime=runtime;
		gameState->powerup.isVisible=1;



		position_t spawnPos = {gameState->dropper.position.x,intToFp(5)*yScale};
		vector_t vel = {intToFp(0), 0x00008000*yScale}; //0x00008000 = 0.5
		gameState->powerup.position=spawnPos;
		gameState->powerup.nextPosition=spawnPos;
		gameState->powerup.velocity=vel;

	}
}

/**
  * @brief  Updates the state of the powerup
  * @param  gameState: the current state of the game
  * @retval None
  */
void updatePowerup(gameState_t* gameState){
	if(gameState->powerup.isVisible){
		gameState->powerup.nextPosition.x=gameState->powerup.position.x+gameState->powerup.velocity.x;
		gameState->powerup.nextPosition.y=gameState->powerup.position.y+gameState->powerup.velocity.y;

		//Checks if the powerup is on level with the player
		if(fpToInt(gameState->powerup.nextPosition.y)/yScale >= fpToInt(gameState->spaceship.position.y)/yScale-3){

			//Checks if the player collides with the powerup
			uint8_t powerupIsTaken;
			if(gameState->spaceship.numberOfParts==3){
				powerupIsTaken = fpToInt(gameState->spaceship.nextPosition.x)+1+spaceshipWidth  >= fpToInt(gameState->powerup.position.x)
				&& fpToInt(gameState->spaceship.nextPosition.x)-1-spaceshipWidth<=fpToInt(gameState->powerup.position.x)+4;
			} else {
			 powerupIsTaken = fpToInt(gameState->spaceship.nextPosition.x)+1+(gameState->spaceship.numberOfParts-1)*spaceshipWidth>=fpToInt(gameState->powerup.position.x)
			&& fpToInt(gameState->spaceship.nextPosition.x)-1<=fpToInt(gameState->powerup.position.x)+4;
			}

			if(powerupIsTaken){
				deletePowerupGraphics(fpToInt(gameState->powerup.position.x),fpToInt(gameState->powerup.position.y)/yScale);
				gameState->powerup.isVisible=0;
				gameState->soundToPlay = 3;
				uint8_t powerupType = rand()%2;

				if(powerupType==0){ //extra spaceship
					if(gameState->spaceship.numberOfParts<3){
						gameState->spaceship.numberOfParts++;
					} else {
						gameState->score += 100;
					}
				} else { //disable enemy canons
					gameState->enemyCanonDisableTime=runtime;
					gameState->enemyCanonsUnchanged =0;
				}
			}
		}

		//Deletes the powerup if below the screen
		if(fpToInt(gameState->powerup.nextPosition.y)/yScale>=fpToInt(gameState->spaceship.position.y)/yScale+1){
			deletePowerupGraphics(fpToInt(gameState->powerup.position.x),fpToInt(gameState->powerup.position.y)/yScale);
			gameState->powerup.isVisible=0;
		}
	}
}

/**
  * @brief  Draw the powerup to the screen
  * @param  gameState: the current state of the game
  * @retval None
  */
void drawPowerup(gameState_t* gameState){
	if(gameState->powerup.isVisible){
		deletePowerupGraphics(fpToInt(gameState->powerup.position.x),fpToInt(gameState->powerup.position.y)/yScale);
		drawPowerupGraphics(fpToInt(gameState->powerup.nextPosition.x),fpToInt(gameState->powerup.nextPosition.y)/yScale);
		gameState->powerup.position=gameState->powerup.nextPosition;
	}
}
