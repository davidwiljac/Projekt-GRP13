/*
 * bullet.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include "bullet.h"


// fra https://www.geeksforgeeks.org/find-two-rectangles-overlap/ (modificeret)
uint8_t rectsOverlap(position_t l1, position_t r1, position_t l2, position_t r2){

		// If one rectangle is on left side of other
		if (l1.x > r2.x || l2.x > r1.x){
			return 0;
		}

		// If one rectangle is above other
		if (r1.y < l2.y || r2.y < l1.y) {
				return 0;
		}
    return 1;
}

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
		//do initial calculations
		position_t bulletTopLftCnr = {0,0};
		position_t bulletDwnRghtCnr = {0,0};

		if(current->bullet.position.x<current->bullet.nextPosition.x){
			bulletTopLftCnr.x=current->bullet.position.x;
			bulletDwnRghtCnr.x=current->bullet.nextPosition.x;
		} else {
			bulletTopLftCnr.x=current->bullet.nextPosition.x;
			bulletDwnRghtCnr.x=current->bullet.position.x;
		}
		if(current->bullet.position.y<current->bullet.nextPosition.y){
			bulletTopLftCnr.y=current->bullet.position.y;
			bulletDwnRghtCnr.y=current->bullet.nextPosition.y;
		} else {
			bulletTopLftCnr.y=current->bullet.nextPosition.y;
			bulletDwnRghtCnr.y=current->bullet.position.y;
		}


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
			position_t spaceshipTopLftCnr= {gameState->spaceship.position.x-intToFp(1),gameState->spaceship.position.y};
			position_t spaceshipDwnLftCnr= {gameState->spaceship.position.x+intToFp(1),gameState->spaceship.position.y+intToFp(1*yScale)};
			hitSpaceship = rectsOverlap(bulletTopLftCnr, bulletDwnRghtCnr, spaceshipTopLftCnr, spaceshipDwnLftCnr);
		}
		else if(gameState->spaceship.numberOfParts==2){
			position_t spaceshipTopLftCnr= {gameState->spaceship.position.x-intToFp(1),gameState->spaceship.position.y};
			position_t spaceshipDwnLftCnr= {gameState->spaceship.position.x+intToFp(8),gameState->spaceship.position.y+intToFp(1*yScale)};
			hitSpaceship = rectsOverlap(bulletTopLftCnr, bulletDwnRghtCnr, spaceshipTopLftCnr, spaceshipDwnLftCnr);
		}
		else if(gameState->spaceship.numberOfParts==3){
			position_t spaceshipTopLftCnr= {gameState->spaceship.position.x-intToFp(8),gameState->spaceship.position.y};
			position_t spaceshipDwnLftCnr= {gameState->spaceship.position.x+intToFp(8),gameState->spaceship.position.y+intToFp(1*yScale)};
			hitSpaceship = rectsOverlap(bulletTopLftCnr, bulletDwnRghtCnr, spaceshipTopLftCnr, spaceshipDwnLftCnr);
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


			position_t enemyDwnRghtCnr = {currentEnemy->enemy->position->x+intToFp(6), currentEnemy->enemy->position->y+intToFp(1*yScale)};


			uint8_t hitEnemy = rectsOverlap(bulletTopLftCnr, bulletDwnRghtCnr, *(currentEnemy->enemy->position), enemyDwnRghtCnr);


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





