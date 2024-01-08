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

#endif /* LINKEDLIST_H_ */
