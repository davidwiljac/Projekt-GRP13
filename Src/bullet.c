/*
 * bullet.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "bullet.h"
void updateBullets(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletLL;
	while (current != NULL) {




//		VED BRUG AF FLOATING POINT (sqrt())
		vector_t v = {intToFp(gameState->moon.x-fpToInt(current->bullet.position.x)), intToFp(gameState->moon.y-fpToInt(current->bullet.position.y))};
		uint32_t vLength = intToFp((int)sqrt(fpToInt(v.x)*fpToInt(v.x)+fpToInt(v.y)*fpToInt(v.y)));
		v = scaleVector(v, fpDivide(intToFp(1),vLength));
		//v har nu længde 1
		vector_t accVec = scaleVector(v, fpDivide(intToFp(gameState->moon.mass),fpMultiply(vLength, vLength)));


//		//UDEN BRUG AF FLOATING POINT (vLength er et estimat)
//		vector_t v = {intToFp(gameState->moon.x)-current->bullet.position.x, intToFp(gameState->moon.y)-current->bullet.position.y};
//		uint32_t vLength = fpMultiply(fpAbs(v.x)+fpAbs(v.y), 0x0000b400); // 0x0000b400 er ca. sqrt(2)/2
//		v = scaleVector(v, fpDivide(intToFp(1),vLength));
//		//v er nu ca. 1 lang
//		vector_t accVec = scaleVector(v, fpDivide(intToFp(gameState->moon.mass),fpMultiply(vLength, vLength)));


		current->bullet.velocity.x+=accVec.x;
		current->bullet.velocity.y+=accVec.y;


		current->bullet.nextPosition.x=current->bullet.position.x+current->bullet.velocity.x;
		current->bullet.nextPosition.y=current->bullet.position.y+current->bullet.velocity.y;
		current = current->nextBulletAddress;
	}

}

void detectBulletHit(gameState_t* gameState){

	bulletNode_t* current = gameState->bulletLL;
	while (current != NULL) {

//		uint8_t distToMoon =fpToInt((fpAbs(intToFp(gameState->moon.x)-current->bullet.position.x))+fpAbs((intToFp(gameState->moon.y)-current->bullet.position.y)));
		vector_t v = {intToFp(gameState->moon.x-fpToInt(current->bullet.position.x)), intToFp(gameState->moon.y-fpToInt(current->bullet.position.y))};
		int distToMoon = (int)sqrt(fpToInt(v.x)*fpToInt(v.x)+fpToInt(v.y)*fpToInt(v.y));
		//TODO: afstandsberegning herover kan optimeres. Den beregnes allerede i updateBullet();

		if(fpToInt(current->bullet.nextPosition.y)<=1 || fpToInt(current->bullet.nextPosition.y)>=43*yScale || fpToInt(current->bullet.nextPosition.x)<=1 ||fpToInt(current->bullet.nextPosition.x)>=153 ||distToMoon<=6){ //TODO: add other boundaries
			deleteBulletNode(&(gameState->bulletLL), current);
		}
		current = current->nextBulletAddress;

	}
}

void drawBullets(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletLL;
	while (current != NULL) {
		gotoxy(fpToInt(current->bullet.position.x), fpToInt(current->bullet.position.y)/yScale); //TODO:
		printf(" ");
		gotoxy(fpToInt(current->bullet.nextPosition.x), fpToInt(current->bullet.nextPosition.y)/yScale);//TODO:
		printf("O");

		current->bullet.position.x=current->bullet.nextPosition.x;
		current->bullet.position.y=current->bullet.nextPosition.y;

		current = current->nextBulletAddress;
	}
}





