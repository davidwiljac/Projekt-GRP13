/*
 * nuke.h
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#ifndef NUKE_H_
#define NUKE_H_

#include "types.h"
#include "drivers.h"
#include "ansi.h"
#include "menu.h"
#include "fixedPoint.h"
#include "linkedList.h"
#include "graphics.h"

void updateNuke(gameState_t* gameState);
void chargeNuke(gameState_t* gameState);
void shootNuke(gameState_t* gameState);

#endif /* NUKE_H_ */
