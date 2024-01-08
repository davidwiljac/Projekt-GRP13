/*
 * bullet.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "bullet.h"
void updateBullets(gameState_t* gameState){

}
void detectBulletHit(gameState_t* gameState);

void drawBullets(bulletNode_t* bulletNodeAddress){
	if(fpToInt(bulletNodeAddress->bullet.position.x)!=-1){ //not an empty bulletNode
		gotoxy(fpToInt(bulletNodeAddress->bullet.position.x), fpToInt(bulletNodeAddress->bullet.position.y));
		printf(" ");
		gotoxy(fpToInt(bulletNodeAddress->bullet.nextPosition.x), fpToInt(bulletNodeAddress->bullet.nextPosition.y));
		printf("H");
	}
	if(bulletNodeAddress->nextBulletNode==0){
		return;
	} else {
		drawBullets(bulletNodeAddress->nextBulletNode);
	}
}

