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

	if(fpAbs(gameState->spaceship.prePosition.x - x) < intToFp(2)){
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
	}
	gameState->spaceship.prePosition.x = gameState->spaceship.position.x;
	gameState->spaceship.nextPosition.x = x;
}


void shootSpaceship(gameState_t* gameState){

	if(centerIsPressed()){
		gameState->soundToPlay = 1;
		for (int i = 0; i<gameState->spaceship.numberOfParts; i++){
			uint32_t levelMultiplier = fpMultiply(intToFp(gameState->score/100) + intToFp(gameState->difficulty), 0x00004000) + intToFp(1); //level * 0.25 + 1
			if(i == 2){
				vector_t bulletVelocity = {intToFp(0),fpMultiply(0xffff8000 * yScale, levelMultiplier)}; //0xffff8000 is -0,5
				position_t bulletPos = {gameState->spaceship.position.x-intToFp(spaceshipWidth), gameState->spaceship.position.y-intToFp(1)*yScale};
				bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};
				appendBullet(&(gameState->bulletLL), bullet);
			} else {
				vector_t bulletVelocity = {intToFp(0),fpMultiply(0xffff8000 * yScale, levelMultiplier)}; //0xffff8000 is -0,5
				position_t bulletPos = {gameState->spaceship.position.x+intToFp(i*spaceshipWidth), gameState->spaceship.position.y-intToFp(1)*yScale};
				bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};
				appendBullet(&(gameState->bulletLL), bullet);
			}
		}
	}

}

void drawSpaceship(gameState_t* gameState){

	deleteAttachmentRods(fpToInt(gameState->spaceship.position.x), fpToInt(gameState->spaceship.position.y)/yScale);
	drawAttachmentRods(fpToInt(gameState->spaceship.nextPosition.x), fpToInt(gameState->spaceship.nextPosition.y)/yScale);

	for (int i = 0; i<gameState->spaceship.numberOfParts; i++){

		if(i == 2){
			deleteMe(fpToInt(gameState->spaceship.position.x)-spaceshipWidth, fpToInt(gameState->spaceship.position.y)/yScale);
			drawMe(fpToInt(gameState->spaceship.nextPosition.x)-spaceshipWidth, fpToInt(gameState->spaceship.nextPosition.y)/yScale);
		} else {
			deleteMe(fpToInt(gameState->spaceship.position.x)+i*spaceshipWidth, fpToInt(gameState->spaceship.position.y)/yScale);
			drawMe(fpToInt(gameState->spaceship.nextPosition.x)+i*spaceshipWidth, fpToInt(gameState->spaceship.nextPosition.y)/yScale);

		}


	}



	gameState->spaceship.position=gameState->spaceship.nextPosition;
}
