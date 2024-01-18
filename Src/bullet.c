#include "bullet.h"



// from https://www.geeksforgeeks.org/find-two-rectangles-overlap/ (modified)
// returns 1 if two given rectangles overlap. returns 0 otherwise.
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


/**
  * @brief  Updates the position of all the bullets according to their velocities and thier velocities according the gravity from the moon
  * @param  gamestate: the current state of the game
  * @retval None
  */
void updateBullets(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletLL;
	//Loops though the bullet linked list
	while (current != NULL) {
		//Gravity calculations for bullets
		vector_t v = {intToFp(gameState->moon.x)-current->bullet.position.x, intToFp(gameState->moon.y)-current->bullet.position.y}; //Creates a vector from bullet to the moon
		current->bullet.distanceToMoon = fpMultiply(fpAbs(v.x)+fpAbs(v.y), 0x0000b400); //Approximates the distance to the moon by multiplying the sum of the vector-coordinates by 2/sqrt(2)
		v = scaleVector(v, fpDivide(intToFp(1),current->bullet.distanceToMoon)); //scales the vector to a length of 1
		vector_t accVec = scaleVector(v, fpDivide(intToFp(gameState->moon.mass),fpMultiply(current->bullet.distanceToMoon, current->bullet.distanceToMoon))); //Scale the vector proportional to the distance to the moon

		//Adds acceleration to the bullets velocity
		current->bullet.velocity.x+=accVec.x;
		current->bullet.velocity.y+=accVec.y;

		//Adds velocity to the bullets position
		current->bullet.nextPosition.x=current->bullet.position.x+current->bullet.velocity.x;
		current->bullet.nextPosition.y=current->bullet.position.y+current->bullet.velocity.y;
		current = current->nextBulletAddress;
	}

}

/**
  * @brief  Checks if a bullets has hit something
  * @param  gamestate: the current state of the game
  * @retval None
  */
void detectBulletHit(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletLL;
	//Loops over all bullets
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

		//Checks if the bullet hit the moon or a wall
		if(hitInertObject){
			deleteBulletNode(&(gameState->bulletLL), current);
			current = current->nextBulletAddress;
			continue;
		}

		//Checks if the bullet hit the spaceship
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

		//If a hit deletes a part of the spaceship
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


		//Loops over all the enemies and checks for hits
		enemyNode_t* currentEnemy = gameState->enemyLL;
		while(currentEnemy != NULL){
			position_t enemyDwnRghtCnr = {currentEnemy->enemy->position->x+intToFp(6), currentEnemy->enemy->position->y+intToFp(1*yScale)};
			uint8_t hitEnemy = rectsOverlap(bulletTopLftCnr, bulletDwnRghtCnr, *(currentEnemy->enemy->position), enemyDwnRghtCnr);

			if(hitEnemy == 1){
				gameState->soundToPlay = 4;
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

/**
  * @brief  draws all the bullets to the screen
  * @param  gamestate: the current state of the game
  * @retval None
  */
void drawBullets(gameState_t* gameState){
	bulletNode_t* current = gameState->bulletLL;

	while (current != NULL) {
		gotoxy(fpToInt(current->bullet.position.x), fpToInt(current->bullet.position.y)/yScale);
		printf(" ");
		gotoxy(fpToInt(current->bullet.nextPosition.x), fpToInt(current->bullet.nextPosition.y)/yScale);
		printf("O");

		current->bullet.position.x=current->bullet.nextPosition.x;
		current->bullet.position.y=current->bullet.nextPosition.y;

		current = current->nextBulletAddress;
	}
}





