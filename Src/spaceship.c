/*
 * spaceship.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "spaceship.h"

void updateSpaceship(gameState_t* gameState){
	uint16_t potVal = readPotentiometer();
<<<<<<< Updated upstream
	uint32_t x = fpDivide(intToFp(potVal), intToFp(13)) ;
	if(fpToInt(x) <= 1){
		x = intToFp(2);
	}
	if(fpToInt(x) >= 156){
		x = intToFp(155);
=======
	uint32_t x = fpDivide(intToFp(potVal), intToFp(13));
	if(fpToInt(fpAbs(gameState->spaceship.prePosition.x - x)) < 5){
		return;
	}

	if(gameState->spaceship.numberOfParts==1){
		if(fpToInt(x) <= 2){
			x = intToFp(3);
		}
		if(fpToInt(x) >= 155){
			x = intToFp(154);
		}
	}

	else if(gameState->spaceship.numberOfParts==2){
		if(fpToInt(x) <= 2){
			x = intToFp(3);
		}
		if(fpToInt(x) >= 155-7){
			x = intToFp(154-7);
		}
	}
	else if(gameState->spaceship.numberOfParts==3){
		if(fpToInt(x) <= 2+7){
			x = intToFp(3+7);
		}
		if(fpToInt(x) >= 155-7){
			x = intToFp(154-7);
		}
>>>>>>> Stashed changes
	}
	gameState->spaceship.prePosition.x = gameState->spaceship.position.x;
	gameState->spaceship.nextPosition.x = x;

}


void shootSpaceship(gameState_t* gameState){

	if(centerIsPressed()){
<<<<<<< Updated upstream
	//if(runtime-gameState->spaceship.lastShotTime>=gameState->spaceship.firingPeriod){

		gameState->spaceship.lastShotTime = runtime;
=======
		gameState->soundToPlay = 1;
		for (int i = 0; i<gameState->spaceship.numberOfParts; i++){
			if(i ==2){
				vector_t bulletVelocity = {intToFp(0),0xffff8000*yScale}; //0xffff8000 is -0,5
				position_t bulletPos = {gameState->spaceship.position.x-intToFp(spaceshipWidth), gameState->spaceship.position.y-intToFp(1)*yScale};
				bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};
				appendBullet(&(gameState->bulletLL), bullet);
			} else {
				vector_t bulletVelocity = {intToFp(0),0xffff8000*yScale}; //0xffff8000 is -0,5
				position_t bulletPos = {gameState->spaceship.position.x+intToFp(i*spaceshipWidth), gameState->spaceship.position.y-intToFp(1)*yScale};
				bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};
				appendBullet(&(gameState->bulletLL), bullet);
			}
>>>>>>> Stashed changes


		vector_t bulletVelocity = {intToFp(0),0xffff8000*yScale}; //0xffff8000 is -0,5
		position_t bulletPos = {gameState->spaceship.position.x, gameState->spaceship.position.y-intToFp(1)};
		bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};

		appendBullet(&(gameState->bulletLL), bullet);
	}
}
