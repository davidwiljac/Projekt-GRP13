/*
 * enemy.h
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#ifndef ENEMY_H_
#define ENEMY_H_
#include "types.h"
#include "drivers.h"
#include "ansi.h"
#include "linkedList.h"
#include "fixedPoint.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define enemyDisableDuration 1000

void spawnEnemy(gameState_t* gameState);
void updateEnemy(gameState_t* gameState);
void shootEnemy(gameState_t* gameState);
void detectCityHit(gameState_t* gameState);
void drawEnemies(gameState_t* gameState);
uint8_t xValIsValid(uint8_t xVal, uint8_t objectWidth);

#endif /* ENEMY_H_ */
