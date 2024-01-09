/*
 * bullet.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "bullet.h"
void updateBullets(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletHead;
	while (current != NULL) {
		current->bullet.nextPosition.x=current->bullet.position.x+current->bullet.velocity.x;
		current->bullet.nextPosition.y=current->bullet.position.y+current->bullet.velocity.y;
		current = current->nextBulletAddress;
	}
}

void detectBulletHit(gameState_t* gameState){

	bulletNode_t* current = gameState->bulletHead;
	while (current != NULL) {


		if(fpToInt(current->bullet.nextPosition.y)<=1){ //TODO: add other boundaries
			deleteBulletNode(&(gameState->bulletHead), current);
		}
		current = current->nextBulletAddress;

	}
}

void drawBullets(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletHead;
	while (current != NULL) {
		gotoxy(fpToInt(current->bullet.position.x), fpToInt(current->bullet.position.y));
		printf(" ");
		gotoxy(fpToInt(current->bullet.nextPosition.x), fpToInt(current->bullet.nextPosition.y));
		printf("O");

		current->bullet.position.x=current->bullet.nextPosition.x;
		current->bullet.position.y=current->bullet.nextPosition.y;

		current = current->nextBulletAddress;
	}
}





