/*
 * enemy.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"enemy.h"

/**
  * @brief  ensure powerups and enemies dont spawn over the moon
  * @param  xVal: the position of the objects, objectWidth: the width of the object
  * @retval 1 = valid, 0 = non-valid
  */
uint8_t xValIsValid(uint8_t xVal, uint8_t objectWidth){ //ensure powerups and enemies dont spawn over the moon
	if ((xVal>=2 && xVal<=63-objectWidth) || (xVal>=77 && xVal<=screenWidth)){
		return 1;
	} else {
		return 0;
	}
}

/**
  * @brief  Checks if it should spawn a new enemy, and if so spawns one
  * @param  gameState: the current state of the game
  * @retval None
  */
void spawnEnemy(gameState_t* gameState){
	//Checks if a enemy should spawn
	if(runtime >= gameState->nextEnemySpawn){
		uint16_t enemyPos = (rand() % 149) + 1; //x-position between 1 and 149

		//Recalculates if position is non-valid
		while(!xValIsValid(enemyPos, 7)){
			enemyPos  = (rand() % 149) + 1;
		}

		//Generates a new enemy and appends to the linked list of enemies
		enemy_t* enemy = malloc(sizeof(enemy_t));
		position_t* pos = malloc(sizeof(position_t));
		pos->x = intToFp(enemyPos);
		pos->y = intToFp(3*yScale);
		enemy->position = pos;

		uint32_t levelMultiplier = fpMultiply(intToFp(gameState->score/100) + intToFp(gameState->difficulty), 0x00004000) + intToFp(1); //(score/100 + difficulty) * 0.25 + 1
		vector_t* vEnemy = malloc(sizeof(vector_t));
		vEnemy->x = intToFp(0);
		vEnemy->y = fpMultiply((0x00004000 * yScale), levelMultiplier); //0.25 * multiplier
		enemy->velocity  = vEnemy;

		position_t* newPos = malloc(sizeof(position_t));
		newPos->x = pos->x;
		newPos->y = pos->y;
		enemy->nextPosition = newPos;

		enemy->lastShotTime = runtime;
		enemy->firingRate = 100; //A second every seconds

		gameState->nextEnemySpawn = runtime + (rand()%200) + 100; //spawns the next enemy after between 100 and 300 centiseconds
		appendEnemy(gameState, enemy);
	}
}

/**
  * @brief  Loops over all the enemies and updates their position based on their velocities
  * @param  gameState: the current state of the game
  * @retval None
  */
void updateEnemy(gameState_t* gameState){
	enemyNode_t* thisNode = gameState->enemyLL;
	while(thisNode != NULL){
		thisNode->enemy->nextPosition->x = thisNode->enemy->position->x + thisNode->enemy->velocity->x;
		thisNode->enemy->nextPosition->y = thisNode->enemy->position->y + thisNode->enemy->velocity->y;
		thisNode = thisNode->nextEnemyNode;
	}
}

/**
  * @brief  Loops over all the enemies and shoots a bullet based on firingRate
  * @param  gameState: the current state of the game
  * @retval None
  */
void shootEnemy(gameState_t* gameState){
	enemyNode_t* thisNode = gameState->enemyLL;
	while(thisNode != NULL){
		//If enough time has passed shoot
		if(thisNode->enemy->lastShotTime + thisNode->enemy->firingRate < runtime){
			vector_t bulletVector = {intToFp(0), intToFp(2)};
			position_t bulletPos = {thisNode->enemy->position->x, thisNode->enemy->position->y + intToFp(2 * yScale)};
			bullet_t bullet = {bulletPos, bulletPos, bulletVector};
			appendBullet(&(gameState->bulletLL), bullet);
			thisNode->enemy->lastShotTime = runtime;
	if(runtime-gameState->enemyCanonDisableTime >= enemyDisableDuration || gameState->enemyCanonsUnchanged){
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
}

/**
  * @brief  Detects if an enemy has hit the bottom of the screen
  * @param  gameState: the current state of the game
  * @retval None
  */
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
		}
		thisNode = thisNode->nextEnemyNode;
	}
}
