/*
 * nuke.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"nuke.h"

void chargeNuke(gameState_t* gameState){
	uint8_t color[] = {0,0,0};
	if(runtime - gameState->nuke->lastActivationTime < 500){
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
		gameState->nuke->readyState = 1;
	}
	int8_t nullColor[] = {0,0,0};
	RGBColor(nullColor);
	RGBColor(color);
}

void detonateNuke(gameState_t* gameState){
	gameState->nuke->isDeployed = 0;
	gameState->nuke->readyState = 0;

	gotoxy(fpToInt(gameState->nuke->position.x),(fpToInt(gameState->nuke->position.y)) / yScale);
	printf("     ");
	gotoxy(fpToInt(gameState->nuke->position.x),(fpToInt(gameState->nuke->position.y) + 1 * yScale) / yScale);
	printf("     ");
	gotoxy(fpToInt(gameState->nuke->position.x),(fpToInt(gameState->nuke->position.y) + 2 * yScale) / yScale);
	printf("     ");
	enemyNode_t* current = gameState->enemyLL;
	drawNukeCircle(gameState);
	gameState->nuke->lastDetonationTime = runtime;
	gameState->nuke->circleClear = 0;
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

void shootNuke(gameState_t* gameState){
	uint8_t x = I2C_Read(0x98, 0x03, 0, 1); //Read output register
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

void updateNuke(gameState_t* gameState){
	chargeNuke(gameState);
	shootNuke(gameState);
	if(gameState->nuke->isDeployed == 1){
		gameState->nuke->nextPosition.x = gameState->nuke->position.x + gameState->nuke->velocity.x;
		gameState->nuke->nextPosition.y = gameState->nuke->position.y + gameState->nuke->velocity.y;
	}
	if(runtime - gameState->nuke->lastDetonationTime > 100 && gameState->nuke->circleClear == 0){
		clearNukeCircle(gameState);
		gameState->nuke->lastDetonationTime = 0xFFFFFFFF;
		gameState->nuke->circleClear = 1;
	}
}
