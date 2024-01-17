/*
 * nuke.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"nuke.h"

/**
  * @brief  Tests how charged the nuke is
  * @param  gameState: the current state of the game
  * @retval None
  */
void chargeNuke(gameState_t* gameState){
	uint8_t color[] = {0,0,0};
	if(runtime - gameState->nuke->lastActivationTime <= 500){
		color[0] = 1;
		color[1] = 0;
		color[2] = 0;
	}
	if(runtime - gameState->nuke->lastActivationTime > 500){
		color[0] = 1;
		color[1] = 0;
		color[2] = 1;
	}
	if(runtime - gameState->nuke->lastActivationTime > 1000){
		color[0] = 1;
		color[1] = 1;
		color[2] = 0;
	}
	if(runtime - gameState->nuke->lastActivationTime > 1500){
		color[0] = 0;
		color[1] = 1;
		color[2] = 0;
		if(gameState->nuke->readyState == 0) gameState->soundToPlay = 2; //Plays the charge sound if it's the first time.
		gameState->nuke->readyState = 1;
	}
	RGBColor(color);
}

/**
  * @brief  Deletes the unexploded nuke, draws the explosion circle and deletes all enemies in a given radius
  * @param  None
  * @retval None
  */
void detonateNuke(gameState_t* gameState){
	//Resets nuke
	gameState->nuke->isDeployed = 0;
	gameState->nuke->readyState = 0;

	//Deletes the unexploded nuke
	gotoxy(fpToInt(gameState->nuke->position.x),(fpToInt(gameState->nuke->position.y)) / yScale);
	printf("     ");
	gotoxy(fpToInt(gameState->nuke->position.x),(fpToInt(gameState->nuke->position.y) + 1 * yScale) / yScale);
	printf("     ");
	gotoxy(fpToInt(gameState->nuke->position.x),(fpToInt(gameState->nuke->position.y) + 2 * yScale) / yScale);
	printf("     ");


	drawNukeCircle(gameState);

	gameState->nuke->lastDetonationTime = runtime;
	gameState->nuke->circleClear = 0;

	//Loops over all the enemies and deletes the ones closer than 35 uints
	enemyNode_t* current = gameState->enemyLL;
	while(current != NULL){
		uint32_t distToEnemy= fpMultiply(fpAbs(gameState->nuke->position.x - current->enemy->position->x +
								fpAbs(gameState->nuke->position.y - current->enemy->position->y)),
				0x0000b400); //Aprox of pythagoras where (x+y) * (sqrt(2)/2)
		if(distToEnemy < intToFp(35)){
			deleteEnemyNode(gameState, current);
		}
		current = current->nextEnemyNode;
	}
}

/**
  * @brief  Checks if the nuke should be deployed and does if so
  * @param  gameState: te current state of the game
  * @retval None
  */
void shootNuke(gameState_t* gameState){
	uint8_t x = I2C_Read(0x98, 0x03, 0, 1); //Read output register of the accelerometer

	//If the 8'th bit (tap-detection) is on and the nuke is ready and deployed if it isn't. If it has be deployed for a second detonate it
	if(x > 128 && gameState->nuke->readyState){
		if(gameState->nuke->isDeployed == 0){
			position_t pos= {gameState->spaceship.position.x, gameState->spaceship.position.y};
			vector_t vec = {0, intToFp(-1)};
			gameState->nuke->position = pos;
			gameState->nuke->nextPosition = pos;
			gameState->nuke->velocity = vec;
			gameState->nuke->isDeployed = 1;
			gameState->nuke->lastActivationTime = runtime;
		}else{
			if(runtime - gameState->nuke->lastActivationTime > 100) detonateNuke(gameState);
		}
	}
}

/**
  * @brief  Update the state of the nuke
  * @param  None
  * @retval None
  */
void updateNuke(gameState_t* gameState){
	chargeNuke(gameState);
	shootNuke(gameState);

	//If the nuke is deployed update it's position
	if(gameState->nuke->isDeployed == 1){
		gameState->nuke->nextPosition.x = gameState->nuke->position.x + gameState->nuke->velocity.x;
		gameState->nuke->nextPosition.y = gameState->nuke->position.y + gameState->nuke->velocity.y;
	}

	//If it's more than 0.1s since detonation and the circle is not clear, clear it.
	if(runtime - gameState->nuke->lastDetonationTime > 100 && gameState->nuke->circleClear == 0){
		clearNukeCircle(gameState);
		gameState->nuke->lastDetonationTime = 0xFFFFFFFF;
		gameState->nuke->circleClear = 1;
	}
}
