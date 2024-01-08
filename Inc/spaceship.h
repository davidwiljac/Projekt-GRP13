/*
 * spaceship.h
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include "stdint.h"
#include "stdio.h"
#include "types.h"
#include "menu.h"
#include "fixedPoint.h"
#include "drivers.h"
#include "linkedList.h"

void updateSpaceship(gameState_t* gameState,  uint8_t* dir);
void shootSpaceship(gameState_t* gameState);

#endif /* SPACESHIP_H_ */
