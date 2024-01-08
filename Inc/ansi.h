/*
 * ansi.h
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#ifndef ANSI_H_
#define ANSI_H_


#include "stdint.h"
#include "stdio.h"
#include "types.h"


void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(int x, int y);
void underline(int underline_on);
void blink(int blink_on);
void inverse(int inverse_on);
void drawBox(int x1, int y1, int x2, int y2, int style);//style: 0=thin, 1=bold


#endif /* ANSI_H_ */
