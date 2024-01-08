/*
 * enemy.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"enemy.h"

void updateEnemy(gameState_t* gameState){
	if(runtime % 100 == 0){
		runtime++;
		int shouldGenEnemy = rand() % 5;      // Returns a pseudo-random integer between 0 and RAND_MAX.
		if(shouldGenEnemy == 0){
			int enemyPos = rand() % 156;
			gotoxy(enemyPos, 5);
			printf(":E");
		}
	}
}

void shootEnemy(gameState_t* gameState){

}

void detectCityHit(gameState_t* gameState){

}
