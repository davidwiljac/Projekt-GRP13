/*
 * spaceship.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "spaceship.h"

void updateSpaceship(gameState_t* gameState){
	if(gameState->direction == -1 && gameState->spaceship.position.x > intToFp(2)){
		gameState->spaceship.nextPosition.x = gameState->spaceship.position.x - intToFp(1);
	}
	if(gameState->direction == 1 && gameState->spaceship.position.x < intToFp(148)){
		gameState->spaceship.nextPosition.x = gameState->spaceship.position.x + intToFp(1);
	}
	/*
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
	*/
}


void shootSpaceship(gameState_t* gameState){

	if(centerIsPressed()){
	//if(runtime-gameState->spaceship.lastShotTime>=gameState->spaceship.firingPeriod){

		gameState->spaceship.lastShotTime = runtime;


		vector_t bulletVelocity = {intToFp(0),0xffff8000*yScale}; //0xffff8000 is -0,5
		position_t bulletPos = {gameState->spaceship.position.x, gameState->spaceship.position.y-intToFp(1)};
		bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};

		appendBullet(&(gameState->bulletLL), bullet);
	}
}
