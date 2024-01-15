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

		//UDEN BRUG AF FLOATING POINT (vLength er et estimat)
		vector_t v = {intToFp(gameState->moon.x)-current->bullet.position.x, intToFp(gameState->moon.y)-current->bullet.position.y};
		current->bullet.distanceToMoon = fpMultiply(fpAbs(v.x)+fpAbs(v.y), 0x0000b400); // 0x0000b400 er ca. sqrt(2)/2
		v = scaleVector(v, fpDivide(intToFp(1),current->bullet.distanceToMoon));
		//v er nu ca. 1 lang
		vector_t accVec = scaleVector(v, fpDivide(intToFp(gameState->moon.mass),fpMultiply(current->bullet.distanceToMoon, current->bullet.distanceToMoon)));


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

		uint8_t distToMoon = fpToInt(current->bullet.distanceToMoon);


		uint8_t hitInertObject = fpToInt(current->bullet.nextPosition.y)<=2*yScale ||
				fpToInt(current->bullet.nextPosition.y)>=43*yScale ||
				fpToInt(current->bullet.nextPosition.x)<=1 ||
				fpToInt(current->bullet.nextPosition.x)>=156 ||
				distToMoon<=6;

		if(hitInertObject){
			deleteBulletNode(&(gameState->bulletLL), current);
			current = current->nextBulletAddress;
			continue;
		}

		uint8_t hitSpaceship;

		if(gameState->spaceship.numberOfParts==1){
			hitSpaceship = fpToInt(current->bullet.nextPosition.y)>=fpToInt(gameState->spaceship.position.y)-1 &&
						(fpToInt(current->bullet.nextPosition.x)>=fpToInt(gameState->spaceship.position.x)-1 &&
						fpToInt(current->bullet.nextPosition.x)<=fpToInt(gameState->spaceship.position.x)+1);
		}
		else if(gameState->spaceship.numberOfParts==2){
			hitSpaceship = fpToInt(current->bullet.nextPosition.y)>=fpToInt(gameState->spaceship.position.y)-1 &&
							(fpToInt(current->bullet.nextPosition.x)>=fpToInt(gameState->spaceship.position.x)-1 &&
							fpToInt(current->bullet.nextPosition.x)<=fpToInt(gameState->spaceship.position.x)+9);
		}
		else if(gameState->spaceship.numberOfParts==3){
			hitSpaceship = fpToInt(current->bullet.nextPosition.y)>=fpToInt(gameState->spaceship.position.y)-1 &&
							(fpToInt(current->bullet.nextPosition.x)>=fpToInt(gameState->spaceship.position.x)-9 &&
							fpToInt(current->bullet.nextPosition.x)<=fpToInt(gameState->spaceship.position.x)+9);
		}

		if(hitSpaceship){

			gameState->soundToPlay = 4;

			if(gameState->spaceship.numberOfParts==3){
				deleteMe(fpToInt(gameState->spaceship.position.x)-7, fpToInt(gameState->spaceship.position.y)/yScale);
				gameState->spaceship.numberOfParts--;
			} else if(gameState->spaceship.numberOfParts==2){
				deleteMe(fpToInt(gameState->spaceship.position.x)+7, fpToInt(gameState->spaceship.position.y)/yScale);
				gameState->spaceship.numberOfParts--;
			}

			deleteBulletNode(&(gameState->bulletLL), current);
			current = current->nextBulletAddress;
			continue;
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
				break;
			}
			currentEnemy = currentEnemy->nextEnemyNode;
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





