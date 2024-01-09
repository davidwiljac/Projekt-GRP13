/*
 * bullet.h
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "types.h"
#include "ansi.h"
#include "fixedPoint.h"

void updateBullets(gameState_t* gameState);
void detectBulletHit(gameState_t* gameState);
void drawBullets(bulletNode_t* head);

#endif /* BULLET_H_ */
