/*
 * menu.h
 *
 *  Created on: 7. jan. 2024
 *      Author: Loren
 */

#ifndef MENU_H_
#define MENU_H_

#include "stdint.h"
#include "stdio.h"
#include "types.h"
#include <string.h>
#include "ansi.h"

#define screenWidth 156
#define screenHeight 43
//IMPORTANT! virtual screen height is 86 (can be changed beneath)

#define yScale 2 //1 is normal, 2 makes the virtual screen height 86




void drawMenuScreen(button_t btnList[], gameState_t* gameState);
void drawHelpScreen();
void drawButton(button_t btn);
void drawBtnAsSelected(button_t btn);
void drawBtnAsDeselected(button_t btn);
void drawWindow();
void drawbackground();
#endif /* MENU_H_ */
