#ifndef SPACESHIP_H_
#define SPACESHIP_H_
#define spaceshipWidth 7

#include "drivers.h"
#include "stdint.h"
#include "stdio.h"
#include "types.h"
#include "menu.h"
#include "fixedPoint.h"
#include "drivers.h"
#include "linkedList.h"
#include "graphics.h"



void updateSpaceship(gameState_t* gameState);
void shootSpaceship(gameState_t* gameState);
void drawSpaceship(gameState_t* gameState);

#endif /* SPACESHIP_H_ */
