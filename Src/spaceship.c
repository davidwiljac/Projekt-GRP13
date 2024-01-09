/*
 * spaceship.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "spaceship.h"

void updateSpaceship(gameState_t* gameState, uint8_t* dir){

	if(fpToInt(gameState->spaceship.position.x)>=screenWidth-1){
		*dir =1;
	} else if(fpToInt(gameState->spaceship.position.x)<=2){
		*dir =0;
	}
	if(*dir==0){
		gameState->spaceship.nextPosition.x=gameState->spaceship.position.x+intToFp(2);
	} else {
		gameState->spaceship.nextPosition.x=gameState->spaceship.position.x-intToFp(2);
	}
}


void shootSpaceship(gameState_t* gameState){
	uint8_t firingPeriod = gameState->spaceship.firingPeriod;


	if(runtime-gameState->spaceship.lastShotTime>=firingPeriod){//
		gameState->spaceship.lastShotTime = runtime;


		vector_t bulletVelocity = {intToFp(0),intToFp(-3)};
		position_t bulletPos = {gameState->spaceship.position.x, gameState->spaceship.position.y-intToFp(1)};
		bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};

		appendBullet(&(gameState->bulletLL), bullet);
	}
}
