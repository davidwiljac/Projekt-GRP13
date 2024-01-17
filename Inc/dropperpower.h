/*
 * dropperpower.h
 *
 *  Created on: 15 Jan 2024
 *      Author: Bivertical
 */

#ifndef DROPPERPOWER_H_
#define DROPPERPOWER_H_

#include "types.h"
#include "drivers.h"
#include "fixedPoint.h"
#include "menu.h"
#include "graphics.h"
#include "ansi.h"

void deletedropper(uint8_t X,uint8_t Y);
void conditiondropper(gameState_t* gameState);
void updatedropper(gameState_t* gameState);
void spawndropper(gameState_t* gameState);


#endif /* DROPPERPOWER_H_ */
