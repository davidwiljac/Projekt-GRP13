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

void appendBullet(gameState_t* gameState, bullet_t bullet);
bulletNode_t* getAdressToLastBulletNode(bulletNode_t* bulletNodeAdress);

void appendEnemy(gameState_t* gameState, enemy_t enemy);
#endif /* LINKEDLIST_H_ */
