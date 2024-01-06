/*
 * enemy.h
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "types.h"

void updateEnemy(gameState_t* gameState);
void shootEnemy(gameState_t* gameState);
void detectCityHit(gameState_t* gameState);

#endif /* ENEMY_H_ */
