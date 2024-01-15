/*
 * enemy.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"enemy.h"

uint8_t xValIsValid(uint8_t xVal, uint8_t objectWidth){ //ensure powerups and enemies dont spawn over the moon
	if ((xVal>=2 && xVal<=63-objectWidth) || (xVal>=77 && xVal<=screenWidth)){
		return 1;
	} else {
		return 0;
	}
}
void spawnEnemy(gameState_t* gameState){
	if(runtime >= gameState->nextEnemySpawn){
		uint16_t enemyPos = (rand() % 149) + 1;

		while(!xValIsValid(enemyPos, 7)){
			enemyPos  = (rand() % 149) + 1;
		}

		enemy_t* enemy = malloc(sizeof(enemy_t));
		position_t* pos = malloc(sizeof(position_t));
		pos->x = intToFp(enemyPos);
		pos->y = intToFp(3*yScale);
		enemy->position = pos;

		uint32_t levelMultiplier = fpMultiply(intToFp(gameState->score/100) + intToFp(gameState->difficulty), 0x00004000) + intToFp(1); //level * 0.25 + 1
		vector_t* vEnemy = malloc(sizeof(vector_t));
		vEnemy->x = intToFp(0);
		vEnemy->y = fpMultiply((0x00004000 * yScale), levelMultiplier);
		enemy->velocity  = vEnemy;

		position_t* newPos = malloc(sizeof(position_t));
		newPos->x = pos->x;
		newPos->y = pos->y;
		enemy->nextPosition = newPos;

		enemy->lastShotTime = runtime;
		enemy->firingRate = 100;

		gameState->nextEnemySpawn = runtime + (rand()%200) + 100; //spawns the next enemy after between 100 and 300 centiseconds
		appendEnemy(gameState, enemy);
	}
}

void updateEnemy(gameState_t* gameState){
	enemyNode_t* thisNode = gameState->enemyLL;
	while(thisNode != NULL){
		thisNode->enemy->nextPosition->x = thisNode->enemy->position->x + thisNode->enemy->velocity->x;
		thisNode->enemy->nextPosition->y = thisNode->enemy->position->y + thisNode->enemy->velocity->y;
		thisNode = thisNode->nextEnemyNode;
	}
}

void shootEnemy(gameState_t* gameState){
	enemyNode_t* thisNode = gameState->enemyLL;
	while(thisNode != NULL){
		if(thisNode->enemy->lastShotTime + thisNode->enemy->firingRate < runtime){
			vector_t bulletVector = {intToFp(0), intToFp(2)};
			position_t bulletPos = {thisNode->enemy->position->x, thisNode->enemy->position->y + intToFp(2 * yScale)};
			bullet_t bullet = {bulletPos, bulletPos, bulletVector};
			appendBullet(&(gameState->bulletLL), bullet);
			thisNode->enemy->lastShotTime = runtime;
		}
		thisNode = thisNode->nextEnemyNode;
	}
}

void detectCityHit(gameState_t* gameState){
	enemyNode_t* thisNode = gameState->enemyLL;
	while(thisNode != NULL){
		if(fpToInt(thisNode->enemy->position->y) >= 40 * yScale){
			gameState->cityLives--;

			if(gameState->cityLives == 2){
				gotoxy(1, 42);
				for(int i = 0; i<screenWidth;i++){
					printf(" ");
				}
			}
			if(gameState->cityLives == 1){
				gotoxy(1, 43);
				for(int i = 0; i<screenWidth;i++){
					printf(" ");
				}
			}
			deleteEnemyNode(gameState, thisNode);
			//drawhearth(gameState);
		}
		thisNode = thisNode->nextEnemyNode;
	}
}
