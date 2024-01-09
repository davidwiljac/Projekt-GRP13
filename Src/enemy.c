/*
 * enemy.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"enemy.h"

void updateEnemy(gameState_t* gameState){
	if(runtime % 100 == 0){
		runtime++;
		int shouldGenEnemy = rand() % 5;      // Returns a pseudo-random integer between 0 and RAND_MAX.
		if(shouldGenEnemy == 0){
			int enemyPos = rand() % 156;

			enemy_t enemy;
			enemy.firingRate = 2;
			position_t pos = {0, enemyPos};
			enemy.position = pos;
			pos.x++;
			enemy.nextPosition = pos;
			appendEnemy(gameState, enemy);
		}
	}
}

void shootEnemy(gameState_t* gameState){

}

void detectCityHit(gameState_t* gameState){

}

void drawEnemies(gameState_t* gameState){
	int isLastElement = 0;
	enemyNode_t* thisNode = gameState->enemyLL;

	while(1){
		gotoxy(thisNode->enemy->nextPosition->y, thisNode->enemy->nextPosition->x);
		printf(":E");
		if(thisNode->nextEnemyNode == -1){
			break;
		}
	}
}
