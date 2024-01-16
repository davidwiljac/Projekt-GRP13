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
void drawMe(uint8_t X, uint8_t Y);
void deleteMe(uint8_t X, uint8_t Y);

void drawbackground();
void drawhearth(gameState_t* gameState);
void drawCity();
void drawScore(gameState_t* gameState);

void drawPowerupGraphics(uint8_t x, uint8_t y);
void deletePowerupGraphics(uint8_t x, uint8_t y);
void drawAttachmentRods(uint8_t x, uint8_t y);
void deleteAttachmentRods(uint8_t x, uint8_t y);

void drawNuke(gameState_t* gameState);
void drawNukeCircle(gameState_t* gameState);
void clearNukeCircle(gameState_t* gameState);

void drawDropper(gameState_t* gameState);


void drawBossKey();
#endif /* GRAPHICS_H_ */
