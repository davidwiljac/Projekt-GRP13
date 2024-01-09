/*
 * graphics.h
 *
 *  Created on: 8 Jan 2024
 *      Author: Bivertical
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "ansi.h"
#include "fixedPoint.h"
#include "stdint.h"
#include "stdio.h"

void drawMoon(uint8_t x, uint8_t y);
void drawEnemy(gameState_t* gameState);
void drawBullet();
void drawMe();
void drawbackground();
void drawhearth(gameState_t* gameState);
void drawCity();

#endif /* GRAPHICS_H_ */
