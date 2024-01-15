/*
 * powerup.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "powerup.h"
#define spawnPeriod 600

void spawnPowerup(gameState_t* gameState){
	if(runtime-gameState->powerup.lastUseTime>=spawnPeriod){



		gameState->powerup.lastUseTime=runtime;
		gameState->powerup.isVisible=1;

		uint8_t randomX;
				while(!xValIsValid(randomX, 5)){
					randomX = (rand() % 147) + 1;
				}

		position_t spawnPos = {intToFp(randomX), intToFp(2)*yScale};
		vector_t vel = {intToFp(0), 0x00008000*yScale};
		gameState->powerup.position=spawnPos;
		gameState->powerup.nextPosition=spawnPos;
		gameState->powerup.velocity=vel;
	}
}

void updatePowerup(gameState_t* gameState){
	if(gameState->powerup.isVisible){

		gameState->powerup.nextPosition.x=gameState->powerup.position.x+gameState->powerup.velocity.x;
		gameState->powerup.nextPosition.y=gameState->powerup.position.y+gameState->powerup.velocity.y;


		if(fpToInt(gameState->powerup.nextPosition.y)/yScale>=fpToInt(gameState->spaceship.position.y)/yScale-3){

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
		if(fpToInt(gameState->powerup.nextPosition.y)/yScale>=fpToInt(gameState->spaceship.position.y)/yScale+1){
			deletePowerupGraphics(fpToInt(gameState->powerup.position.x),fpToInt(gameState->powerup.position.y)/yScale);
			gameState->powerup.isVisible=0;
		}
	}
}

void drawPowerup(gameState_t* gameState){

	if(gameState->powerup.isVisible){
			deletePowerupGraphics(fpToInt(gameState->powerup.position.x),fpToInt(gameState->powerup.position.y)/yScale);
			drawPowerupGraphics(fpToInt(gameState->powerup.nextPosition.x),fpToInt(gameState->powerup.nextPosition.y)/yScale);

			gameState->powerup.position=gameState->powerup.nextPosition;

		}
}
