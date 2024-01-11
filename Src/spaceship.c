/*
 * spaceship.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "spaceship.h"

void updateSpaceship(gameState_t* gameState){
	/*
	if(gameState->direction == -1 && gameState->spaceship.position.x > intToFp(2)){
		gameState->spaceship.nextPosition.x = gameState->spaceship.position.x - intToFp(1);
	}
	if(gameState->direction == 1 && gameState->spaceship.position.x < intToFp(148)){
		gameState->spaceship.nextPosition.x = gameState->spaceship.position.x + intToFp(1);
	}*/
	uint16_t potVal = readPotentiometer();
	uint32_t x = fpDivide(intToFp(potVal), intToFp(13)) ;
	if(fpToInt(x) <= 1){
		x = intToFp(2);
	}
	if(fpToInt(x) >= 156){
		x = intToFp(155);
	}
	gotoxy(10,10);
	printf("               ");
	gotoxy(10,10);
	printf("%d, %d", potVal, fpToInt(x));
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
