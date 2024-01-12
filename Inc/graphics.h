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
#include "menu.h"

void drawMoon(uint8_t x, uint8_t y);
void drawEnemy(gameState_t* gameState);
void drawBullet(uint8_t X, uint8_t Y);
void drawMe(uint8_t X, uint8_t Y);
void Moongravity();

void drawbackground();
void drawhearth(gameState_t* gameState);
void drawCity();
void drawScore(gameState_t* gameState);

#endif /* GRAPHICS_H_ */
