/*
 * enemy.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"enemy.h"
void spawnEnemy(gameState_t* gameState){
	int shouldGenEnemy = rand() % 50;      // Returns a pseudo-random integer [0:32].
	if(shouldGenEnemy == 0){
		int8_t enemyPos = rand() % 156;
<<<<<<< Updated upstream
=======
		//TODO: Fix tilfældighedsgenerator

>>>>>>> Stashed changes

		enemy_t* enemy = malloc(sizeof(enemy_t));
		enemy->firingRate = 2;
		position_t* pos = malloc(sizeof(position_t));
		pos->x = intToFp(enemyPos);
		pos->y = intToFp(2);
		enemy->position = pos;


		vector_t* vEnemy = malloc(sizeof(vector_t));
		vEnemy->x = intToFp(0);
<<<<<<< Updated upstream
		vEnemy->y = 0x0040;
=======
		vEnemy->y = 0x00004000 * yScale;
>>>>>>> Stashed changes
		enemy->velocity  = vEnemy;

		position_t* newPos = malloc(sizeof(position_t));
		newPos->x = pos->x;
		newPos->y = pos->y;
		enemy->nextPosition = newPos;

		enemy->lastShotTime = runtime;
		enemy->firingRate = 100;
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
			position_t bulletPos = {thisNode->enemy->position->x, thisNode->enemy->position->y + intToFp(1)};
			bullet_t bullet = {bulletPos, bulletPos, bulletVector};
			appendBullet(&(gameState->bulletLL), bullet);
			thisNode->enemy->lastShotTime = runtime;
		}
		thisNode = thisNode->nextEnemyNode;
	}
	/*
	uint8_t firingPeriod = gameState->enemyLL->enemy->firingPeriod;


	if(runtime-gameState->spaceship.lastShotTime>=firingPeriod){//
		gameState->spaceship.lastShotTime = runtime;


		vector_t bulletVelocity = {intToFp(0),intToFp(-3)};
		position_t bulletPos = {gameState->spaceship.position.x, gameState->spaceship.position.y-intToFp(1)};
		bullet_t bullet = {bulletPos, bulletPos, bulletVelocity};

		appendBullet(&(gameState->bulletLL), bullet);
	}*/
}

void detectCityHit(gameState_t* gameState){
	enemyNode_t* thisNode = gameState->enemyLL;
	while(thisNode != NULL){
<<<<<<< Updated upstream
		if(fpToInt(thisNode->enemy->position->y) >= 40){
			//gameState->cityLives--;
=======
		if(fpToInt(thisNode->enemy->position->y) >= 40 * yScale){
			gameState->cityLives--;
>>>>>>> Stashed changes
			deleteEnemyNode(gameState, thisNode);
			drawhearth(gameState);
		}
		thisNode = thisNode->nextEnemyNode;
	}
}
