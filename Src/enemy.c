/*
 * enemy.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"enemy.h"
void spawnEnemy(gameState_t* gameState){
	int shouldGenEnemy = rand() % 100;      // Returns a pseudo-random integer [0:49].
	if(shouldGenEnemy == 0){
		int8_t enemyPos = rand() % 156;

		enemy_t* enemy = malloc(sizeof(enemy_t));
		enemy->firingRate = 2;
		position_t* pos = malloc(sizeof(position_t));
		pos->x = intToFp(enemyPos);
		pos->y = intToFp(2);
		enemy->position = pos;


		vector_t* vEnemy = malloc(sizeof(vector_t));
		vEnemy->x = intToFp(0);
		vEnemy->y = 0x0040;
		enemy->velocity  = vEnemy;

		position_t* newPos = malloc(sizeof(position_t));
		newPos->x = pos->x;
		newPos->y = pos->y;
		enemy->nextPosition = newPos;

		appendEnemy(gameState, enemy);
	}
}

void updateEnemy(gameState_t* gameState){
	enemyNode_t* thisNode = gameState->enemyLL;
	while(1){
		if(thisNode->enemy->position->x != 0){
			thisNode->enemy->nextPosition->x = thisNode->enemy->position->x + thisNode->enemy->velocity->x;
			thisNode->enemy->nextPosition->y = thisNode->enemy->position->y + thisNode->enemy->velocity->y;
		}
		if(thisNode->nextEnemyNode == 0){
			break;
		}
		thisNode = thisNode->nextEnemyNode;
	}
}

void shootEnemy(gameState_t* gameState){

}

void detectCityHit(gameState_t* gameState){

}
