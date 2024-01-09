/*
 * linkedList.c
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#include "linkedList.h"



bulletNode_t* createBulletNode(bullet_t bullet) {
    bulletNode_t* newNode = (bulletNode_t*)malloc(sizeof(bulletNode_t));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->bullet = bullet;
    newNode->nextBulletAddress = NULL;
    return newNode;
}


void appendBullet(bulletNode_t** head, bullet_t bullet) {
    bulletNode_t* newNode = createBulletNode(bullet);
    if (*head == NULL) {
        // If the list is empty, make the new node the head
        *head = newNode;
    } else {
        // Traverse to the end of the list and append the new node
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
	int8_t isEndOfList = 0;
	while(isEndOfList == 0){
		if(thisNode->nextEnemyNode == 0){
			isEndOfList = 1;
			thisNode->nextEnemyNode = newEnemy;
		}else{
			thisNode = thisNode->nextEnemyNode;
		}
	}
void deleteBulletNode(bulletNode_t** head, bulletNode_t* nodeToDelete) {

    if (*head == NULL || nodeToDelete == NULL) {
        // If the list is empty or the node to be deleted is NULL, do nothing
        return;
    }

    gotoxy(fpToInt(nodeToDelete->bullet.position.x), fpToInt(nodeToDelete->bullet.position.y));
    printf(" ");

    // If the node to be deleted is the head of the list
    if (*head == nodeToDelete) {
        *head = nodeToDelete->nextBulletAddress;  // Update the head to the next node
        free(nodeToDelete);  // Free the memory of the deleted node
        return;
    }

    // If the node to be deleted is not the head, traverse the list to find the previous node
    bulletNode_t* current = *head;
    while (current != NULL && current->nextBulletAddress != nodeToDelete) {
        current = current->nextBulletAddress;
    }

    if (current == NULL) {
        // Node to be deleted is not found in the list
        return;
    }

    // Update the next pointer of the previous node to skip the node to be deleted
    current->nextBulletAddress = nodeToDelete->nextBulletAddress;

    // Free the memory of the deleted node

    free(nodeToDelete);

}

//void appendEnemy(gameState_t* gameState, enemy_t enemy){
//	enemyNode_t* newEnemy = malloc(sizeof(enemyNode_t));
//	newEnemy->enemy = enemy;
//	newEnemy->nextEnemyNode = -1;
//
//	enemyNode_t thisNode = gameState->enemyLL;
//	int8_t isEndOfList = 0;
//	while(isEndOfList == 0){
//		if(thisNode.nextEnemyNode == -1){
//			isEndOfList = 1;
//			thisNode.nextEnemyNode = &newEnemy;
//		}else{
//			thisNode = *thisNode.nextEnemyNode;
//		}
//	}
//}


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


