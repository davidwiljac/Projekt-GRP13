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
}



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



//void deleteNode(node_t** head, int data) {
//    if (*head == NULL) {
//        printf("List is empty. Cannot delete.\n");
//        return;
//    }
//
//    node_t* current = *head;
//    node_t* previous = NULL;
//
//    // Traverse the list to find the node with the specified data
//    while (current != NULL && current->data != data) {
//        previous = current;
//        current = current->nextNodeAddress;
//    }
//
//    if (current == NULL) {
//        // Node with the specified data not found
//        printf("Node with data %d not found. Cannot delete.\n", data);
//        return;
//    }
//
//    // Update pointers to bypass the node to be deleted
//    if (previous == NULL) {
//        // If the node to be deleted is the head
//        *head = current->nextNodeAddress;
//    } else {
//        previous->nextNodeAddress = current->nextNodeAddress;
//    }
//
//    // Free the memory allocated for the node to be deleted
//    free(current);
//}
