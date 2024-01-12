/*
 * spaceship.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "spaceship.h"

void updateSpaceship(gameState_t* gameState){
	uint16_t potVal = readPotentiometer();
	uint32_t x = fpDivide(intToFp(potVal), intToFp(13)) ;
	if(fpToInt(x) <= 1){
		x = intToFp(2);
	}
	if(fpToInt(x) >= 156){
		x = intToFp(155);
	}
	gameState->spaceship.nextPosition.x = x;

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
