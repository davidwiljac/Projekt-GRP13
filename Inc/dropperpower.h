#ifndef DROPPERPOWER_H_
#define DROPPERPOWER_H_

#include "types.h"
#include "drivers.h"
#include "fixedPoint.h"
#include "menu.h"
#include "graphics.h"
#include "ansi.h"
#include "powerup.h"

void deleteDropper(uint8_t X,uint8_t Y);
void conditionDropper(gameState_t* gameState);
void updateDropper(gameState_t* gameState);
void spawnDropper(gameState_t* gameState);


#endif /* DROPPERPOWER_H_ */
