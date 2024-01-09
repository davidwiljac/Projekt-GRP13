/*
 * linkedList.h
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "types.h"
#include "fixedPoint.h"
#include "ansi.h"
#include <stdio.h>
#include <stdlib.h>

void appendBullet(bulletNode_t** head, bullet_t bullet);
bulletNode_t* createBulletNode(bullet_t bullet);

void appendEnemy(gameState_t* gameState, enemy_t* enemy);
void deleteEnemyNode(gameState_t* gameState, enemyNode_t* enemy);
#endif /* LINKEDLIST_H_ */
