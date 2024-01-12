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
<<<<<<< Updated upstream
=======
		//UDEN BRUG AF FLOATING POINT (vLength er et estimat)
		vector_t v = {intToFp(gameState->moon.x)-current->bullet.position.x, intToFp(gameState->moon.y)-current->bullet.position.y};
		uint32_t vLength = fpMultiply(fpAbs(v.x)+fpAbs(v.y), 0x0000b400); // 0x0000b400 er ca. sqrt(2)/2
		v = scaleVector(v, fpDivide(intToFp(1),vLength));
		//v er nu ca. 1 lang
		vector_t accVec = scaleVector(v, fpDivide(intToFp(gameState->moon.mass),fpMultiply(vLength, vLength)));


		current->bullet.velocity.x+=accVec.x;
		current->bullet.velocity.y+=accVec.y;


>>>>>>> Stashed changes
		current->bullet.nextPosition.x=current->bullet.position.x+current->bullet.velocity.x;
		current->bullet.nextPosition.y=current->bullet.position.y+current->bullet.velocity.y;
		current = current->nextBulletAddress;
	}
}

<<<<<<< Updated upstream
void detectBulletHit(gameState_t* gameState){}

<<<<<<< Updated upstream
void drawBullets(bulletNode_t* head){
	bulletNode_t* current = head;
=======
	bulletNode_t* current = gameState->bulletLL;
	while (current != NULL) {
		//Detect upper bound
		if(fpToInt(current->bullet.nextPosition.y)<=1){ //TODO: add other boundaries
			deleteBulletNode(&(gameState->bulletLL), current);
		}

		//Detect lower bound
		if(fpToInt(current->bullet.nextPosition.y)>=45){ //TODO: add other boundaries
			deleteBulletNode(&(gameState->bulletLL), current);
		}

		//Detect enemy hit
		while(1){
			enemyNode_t* currentEnemy = gameState->enemyLL;
			break;

=======
void detectBulletHit(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletLL;
	while (current != NULL) {
		//Check if bullet hit a wall or the moon
		vector_t v = {intToFp(gameState->moon.x-fpToInt(current->bullet.position.x)), intToFp(gameState->moon.y-fpToInt(current->bullet.position.y))};
		int distToMoon = (int)sqrt(fpToInt(v.x)*fpToInt(v.x)+fpToInt(v.y)*fpToInt(v.y));
		//TODO: afstandsberegning herover kan optimeres. Den beregnes allerede i updateBullet();

		int8_t hitInertObject = 0;
		hitInertObject = fpToInt(current->bullet.nextPosition.y)<=2 ||
				fpToInt(current->bullet.nextPosition.y)>=43*yScale ||
				fpToInt(current->bullet.nextPosition.x)<=0 ||
				fpToInt(current->bullet.nextPosition.x)>=156 ||
				distToMoon<=6;

		if(hitInertObject){ //TODO: add other boundaries
			deleteBulletNode(&(gameState->bulletLL), current);
		}

		//Check if the bullet hit an enemy
		enemyNode_t* currentEnemy = gameState->enemyLL;
		while(currentEnemy != NULL){
			uint8_t hitEnemy = 0;
			hitEnemy = (fpToInt(current->bullet.position.x) >= fpToInt(currentEnemy->enemy->position->x) &&
					fpToInt(current->bullet.position.x) <= fpToInt(currentEnemy->enemy->position->x) + 7 &&
					fpToInt(current->bullet.position.y) >= fpToInt(currentEnemy->enemy->position->y) &&
					fpToInt(current->bullet.position.y) <= fpToInt(currentEnemy->enemy->position->y) + 1 * yScale);
			if(hitEnemy == 1){
				gameState->score += 10;
				drawScore(gameState);
				deleteBulletNode(&(gameState->bulletLL), current);
				deleteEnemyNode(gameState, currentEnemy);
			}
			currentEnemy = currentEnemy->nextEnemyNode;
>>>>>>> Stashed changes
		}



		current = current->nextBulletAddress;

	}
}

void drawBullets(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletLL;
>>>>>>> Stashed changes
	while (current != NULL) {
		gotoxy(fpToInt(current->bullet.position.x), fpToInt(current->bullet.position.y));
		printf(" ");
		gotoxy(fpToInt(current->bullet.nextPosition.x), fpToInt(current->bullet.nextPosition.y));
		printf("H");

		current->bullet.position.x=current->bullet.nextPosition.x;
		current->bullet.position.y=current->bullet.nextPosition.y;

		current = current->nextBulletAddress;
	}
}





