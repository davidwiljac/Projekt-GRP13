/*
 * linkedList.c
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#include "linkedList.h"



bulletNode_t* createBulletNode(bullet_t bullet) {
    bulletNode_t* newNode = (bulletNode_t*)malloc(sizeof(bulletNode_t));
    newNode->bullet = bullet;
    newNode->nextBulletAddress = NULL;
    return newNode;
}


void appendBullet(bulletNode_t** head, bullet_t bullet) {
    bulletNode_t* newNode = createBulletNode(bullet);
    if (*head == NULL) {
        *head = newNode;
    } else {
        bulletNode_t* current = *head;
        while (current->nextBulletAddress != NULL) {
            current = current->nextBulletAddress;
        }
        current->nextBulletAddress = newNode;
    }
}

void appendEnemy(gameState_t* gameState, enemy_t* enemy){
	enemyNode_t* newEnemy = malloc(sizeof(enemyNode_t));
	newEnemy->enemy = enemy;
	newEnemy->nextEnemyNode = 0;

	enemyNode_t* thisNode = gameState->enemyLL;
	if(gameState->enemyLL == NULL){
		gameState->enemyLL = newEnemy;
	}
	while(thisNode != NULL){
		if(thisNode->nextEnemyNode == NULL){
			thisNode->nextEnemyNode = newEnemy;
			break;
		}
		thisNode = thisNode->nextEnemyNode;
	}
}

void deleteEnemyNode(gameState_t* gameState, enemyNode_t* enemy){
	enemyNode_t* preNode = NULL;
	enemyNode_t* thisNode = gameState->enemyLL;

	if(gameState->enemyLL == enemy){
		gotoxy(fpToInt(enemy->enemy->position->x), fpToInt(enemy->enemy->position->y));
		printf("  ");
		gameState->enemyLL = gameState->enemyLL->nextEnemyNode;
		free(enemy);
		return;
	}

	while(thisNode != NULL){
		if(thisNode == enemy){
			gotoxy(fpToInt(thisNode->enemy->position->x), fpToInt(thisNode->enemy->position->y));
			printf("  ");
			preNode->nextEnemyNode = thisNode->nextEnemyNode;
			free(thisNode->enemy->nextPosition);
			free(thisNode->enemy->position);
			free(thisNode->enemy->velocity);
			free(thisNode->enemy);
			return;
		}
		preNode = thisNode;
		thisNode = thisNode->nextEnemyNode;
	}
}

void deleteBulletNode(bulletNode_t** head, bulletNode_t* nodeToDelete) {

    if (*head == NULL || nodeToDelete == NULL) {
        return;
    }

    gotoxy(fpToInt(nodeToDelete->bullet.position.x), fpToInt(nodeToDelete->bullet.position.y));
    printf(" ");

    if (*head == nodeToDelete) {
        *head = nodeToDelete->nextBulletAddress;
        free(nodeToDelete);
        return;
    }

    bulletNode_t* current = *head;
    while (current != NULL && current->nextBulletAddress != nodeToDelete) {
        current = current->nextBulletAddress;
    }
    current->nextBulletAddress = nodeToDelete->nextBulletAddress;
    free(nodeToDelete);
}



//
//// Function to free the memory allocated for the linked list
//void freeList(node_t* head) {
//    node_t* current = head;
//    node_t* nextNode;
//    while (current != NULL) {
//        nextNode = current->nextNodeAddress;
//        free(current);
//        current = nextNode;
//    }
//}


