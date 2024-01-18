#ifndef POWERUP_H_
#define POWERUP_H_

#include "types.h"
#include "drivers.h"
#include "fixedPoint.h"
#include "menu.h"
#include "graphics.h"
#include "spaceship.h"
#include "enemy.h"

void spawnPowerup(gameState_t* gameState);
void updatePowerup(gameState_t* gameState);
void drawPowerup(gameState_t* gameState);

#endif /* POWERUP_H_ */
