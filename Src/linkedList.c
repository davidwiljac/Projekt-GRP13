/*
 * linkedList.c
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#include "linkedList.h"

/**
  * @brief  Adds a new buletNode to the ends of the bullet linked list
  * @param  head: the head of the bullet list, bullet: the bullet to append
  * @retval None
  */
void appendBullet(bulletNode_t** head, bullet_t bullet) {
    bulletNode_t* newNode = (bulletNode_t*)malloc(sizeof(bulletNode_t));
    newNode->bullet = bullet;
    newNode->nextBulletAddress = NULL;
    //If the list is empty assign the bullet as head
    if (*head == NULL) {
        *head = newNode;
    } else {
    	//Loops through the entire list and adds bullet to the end
        bulletNode_t* current = *head;
        while (current->nextBulletAddress != NULL) {
            current = current->nextBulletAddress;
        }
        current->nextBulletAddress = newNode;
    }
}

/**
  * @brief  Adds a new enemyNode to the ends of the bullet linked list
  * @param  gameState: the current state of the game,  enemy: the enemy to append
  * @retval None
  */
void appendEnemy(gameState_t* gameState, enemy_t* enemy){
	enemyNode_t* newEnemy = malloc(sizeof(enemyNode_t));
	newEnemy->enemy = enemy;
	newEnemy->nextEnemyNode = NULL;

    //If the list is empty assign the enemy as head
	if(gameState->enemyLL == NULL){
		gameState->enemyLL = newEnemy;
	}

	//Loops through the entire list and adds bullet to the end
	enemyNode_t* thisNode = gameState->enemyLL;
	while(thisNode != NULL){
		if(thisNode->nextEnemyNode == NULL){
			thisNode->nextEnemyNode = newEnemy;
			break;
		}
		thisNode = thisNode->nextEnemyNode;
	}
}

/**
  * @brief  deletes a given enemy node
  * @param  gameState: the current state of the game,  enemy: the enemy to delete
  * @retval None
  */
void deleteEnemyNode(gameState_t* gameState, enemyNode_t* enemy){
	enemyNode_t* preNode = NULL;
	enemyNode_t* thisNode = gameState->enemyLL;

	///If the enemy to delete is the first delete the head, sets the head as the second element, and free the memory
	if(gameState->enemyLL == enemy){
		gotoxy(fpToInt(enemy->enemy->position->x), fpToInt(enemy->enemy->position->y)/yScale);
		printf("       ");
		gotoxy(fpToInt(enemy->enemy->position->x), (fpToInt(enemy->enemy->position->y) + 1 * yScale)/yScale);
		printf("       ");
		gameState->enemyLL = gameState->enemyLL->nextEnemyNode;
		free(enemy);
		return;
	}

	///Loops through the entire list of enemies and deletes the given enemy. Also "links" the previous element to the next, and frees memory
	while(thisNode != NULL){
		if(thisNode == enemy){
			gotoxy(fpToInt(enemy->enemy->position->x), fpToInt(enemy->enemy->position->y)/yScale);
			printf("       ");
			gotoxy(fpToInt(enemy->enemy->position->x), (fpToInt(enemy->enemy->position->y) + 1 * yScale)/yScale);
			printf("       ");
			preNode->nextEnemyNode = thisNode->nextEnemyNode;
			free(thisNode->enemy->nextPosition);
			free(thisNode->enemy->position);
			free(thisNode->enemy->velocity);
			free(thisNode->enemy);
			free(thisNode);
			return;
		}
		preNode = thisNode;
		thisNode = thisNode->nextEnemyNode;
	}
}

/**
  * @brief  Deletes an element from the bulletList
  * @param  head: the head of the bullet list, nodeToDelete: the bullet to delete
  * @retval None
  */
void deleteBulletNode(bulletNode_t** head, bulletNode_t* nodeToDelete) {

    if (*head == NULL || nodeToDelete == NULL) {
        return;
    }

    gotoxy(fpToInt(nodeToDelete->bullet.position.x), fpToInt(nodeToDelete->bullet.position.y)/yScale);
    printf(" ");

	///If the enemy to delete is the first delete the head, sets the head as the second element, and free the memory
    if (*head == nodeToDelete) {
        *head = nodeToDelete->nextBulletAddress;
        free(nodeToDelete);
        return;
    }

	///Loops through the entire list of bullets and deletes the given bullet. Also "links" the previous element to the next, and frees memory
    bulletNode_t* current = *head;
    while (current != NULL && current->nextBulletAddress != nodeToDelete) {
        current = current->nextBulletAddress;
    }
    current->nextBulletAddress = nodeToDelete->nextBulletAddress;
    free(nodeToDelete);
}

