#include "spaceship.h"

/**
  * @brief  Updates the position of the spaceship
  * @param  gameState: the current state of the game
  * @retval None
  */
void updateSpaceship(gameState_t* gameState){
	//Reads the potentiometer and calculates the x-value by dividing it by 13 (2048 / 156) (2048 is half of the potentiometer range)
	uint16_t potVal = readPotentiometer();
	uint32_t x = fpDivide(intToFp(potVal), intToFp(13)) ;

	//Anti jitter
	if(fpAbs(gameState->spaceship.prePosition.x - x) < intToFp(2)){
		return;
	}

	//Stops the spaceship at the edges
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

/**
  * @brief  Shoot a bullet if center is pressed
  * @param  gameState: the current state of the game
  * @retval None
  */
void shootSpaceship(gameState_t* gameState){

	if(centerIsPressed()){
		gameState->soundToPlay = 1;
		uint32_t levelMultiplier = fpMultiply(intToFp(gameState->score/100) + intToFp(gameState->difficulty), 0x00004000) + intToFp(1); //level * 0.25 + 1

		//Shoots a bullet for each part of the ship
		for (int i = 0; i < gameState->spaceship.numberOfParts; i++){

			if(i == 2){
				vector_t bulletVelocity = {intToFp(0),fpMultiply(0xffff8000 * yScale, levelMultiplier)}; //{0, -0,5 * Multiplier}
				position_t bulletPos = {gameState->spaceship.position.x-intToFp(spaceshipWidth), gameState->spaceship.position.y-intToFp(1)*yScale};
				bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};
				appendBullet(&(gameState->bulletLL), bullet);
			} else {
				vector_t bulletVelocity = {intToFp(0),fpMultiply(0xffff8000 * yScale, levelMultiplier)}; //{0, -0,5 * Multiplier}
				position_t bulletPos = {gameState->spaceship.position.x+intToFp(i*spaceshipWidth), gameState->spaceship.position.y-intToFp(1)*yScale};
				bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};
				appendBullet(&(gameState->bulletLL), bullet);
			}
		}
	}
}

/**
  * @brief  Draws the spaceship to the screen
  * @param  gameState: the current state of the game
  * @retval None
  */
void drawSpaceship(gameState_t* gameState){
	//Draw attachment points
	deleteAttachmentRods(fpToInt(gameState->spaceship.position.x), fpToInt(gameState->spaceship.position.y)/yScale);
	drawAttachmentRods(fpToInt(gameState->spaceship.nextPosition.x), fpToInt(gameState->spaceship.nextPosition.y)/yScale);

	//Draw all the parts
	for (int i = 0; i < gameState->spaceship.numberOfParts; i++){
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
