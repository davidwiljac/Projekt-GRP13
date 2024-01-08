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

