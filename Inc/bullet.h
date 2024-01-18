#ifndef BULLET_H_
#define BULLET_H_

#include "types.h"
#include "ansi.h"
#include "fixedPoint.h"
#include "linkedList.h"
#include "drivers.h"
#include "math.h"
#include "menu.h"
#include "graphics.h"

void updateBullets(gameState_t* gameState);
void detectBulletHit(gameState_t* gameState);
void drawBullets(gameState_t* gameState);

#endif /* BULLET_H_ */
