/*
 * linkedList.c
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#include "linkedList.h"


//int depth = 0;
bulletNode_t* getAdressToLastBulletNode(bulletNode_t* bulletNodeAdress){
//	depth++;
	if(bulletNodeAdress->nextBulletNode==0){
//		gotoxy(10,10);
//		printf("%d", depth);
		return bulletNodeAdress;
	} else {
		return getAdressToLastBulletNode(bulletNodeAdress->nextBulletNode);
	}
}

//The first bulletNode is empty if bullet position is {intToFp(-1),intToFp(-1)}
void appendBullet(gameState_t* gameState, bullet_t bullet){
	bulletNode_t* lastBulletNodeAdress = getAdressToLastBulletNode(&(gameState->bulletLL));
	bulletNode_t newBulletNode = {bullet, 0};
	lastBulletNodeAdress->nextBulletNode=&newBulletNode;
}

void appendEnemy(gameState_t* gameState, enemy_t enemy){
	enemyNode_t* newEnemy = malloc(sizeof(enemyNode_t));
	newEnemy->enemy = enemy;
	newEnemy->nextEnemyNode = -1;

	enemyNode_t thisNode = gameState->enemyLL;
	int8_t isEndOfList = 0;
	while(isEndOfList == 0){
		if(thisNode.nextEnemyNode == -1){
			isEndOfList = 1;
			thisNode.nextEnemyNode = &newEnemy;
		}else{
			thisNode = *thisNode.nextEnemyNode;
		}
	}
}

