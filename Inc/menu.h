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

void drawMenuScreen(button_t btnList[], gameState_t* gameState);
void drawHelpScreen();
void drawButton(button_t btn);
void drawBtnAsSelected(button_t btn);
void drawBtnAsDeselected(button_t btn);

#endif /* MENU_H_ */
