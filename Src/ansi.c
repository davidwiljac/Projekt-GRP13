/*
 * ansi.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#define ESC 0x1B
#include "ansi.h"

/**
  * @brief  Sets the foreground color of text TODO:REF
  * @param  the color to be set
  * @retval None
  */
void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

/**
  * @brief  Sets the background color of text TODO:REF
  * @param  the color to be set
  * @retval None
  */
void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

/**
  * @brief  combination of fgcolor() and bgcolor() - uses less bandwidth TODO:REF
  * @param  the colors to be set
  * @retval None
  */
void color(uint8_t foreground, uint8_t background) {
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

/**
  * @brief  sets gray on black text, no underline, no blink, no reverse TODO:REF
  * @param  None
  * @retval None
  */
void resetbgcolor() {
  printf("%c[m", ESC);
}

/**
  * @brief  clears the screen TODO:REF
  * @param  None
  * @retval None
  */
void clrscr(){
    printf("%c[H", ESC);
    printf("%c[J", ESC);
}

/**
  * @brief  Sends cursor to the given coordinate TODO:REF
  * @param  x: x-part, y: y-part
  * @retval None
  */
void gotoxy(int x, int y){
    printf("%c[%d;%dH", ESC, y, x);
}

/**
  * @brief  Draws a box from given coordiantes TODO:REF
  * @param  x1: x of top left, y1: y of top left, x2: x of bottom right, y2: y of bottom right, style: the style of box 0=thin 1=bold
  * @retval None
  */
void drawBox(int x1, int y1, int x2, int y2, int style) {
	if(style == 1) {
		 for(int y = y1; y <= y2; y++){
			 gotoxy(x1,y);
			 if (y==y1){
				printf("%c", 201);
			 }
			 else if(y==y2){
				printf("%c", 200);
			 }
			 else {
				printf("%c", 186);
			 }
		   		 }
   		 for(int x = x1; x <= x2; x++){
   			 if(x!=x1){
				 gotoxy(x,y1);
				 printf("%c", 205);
				 gotoxy(x,y2);
				 printf("%c", 205);
   			 }
   		 }
   		 for(int y = y1; y <= y2; y++){
   			 gotoxy(x2,y);
   			 if (y==y1){
				printf("%c", 187);
			 }
			 else if(y==y2){
				printf("%c", 188);
			 }
			 else {
				printf("%c", 186);
			 }
   		 }
	} else {
		for(int y = y1; y <= y2; y++){
			 gotoxy(x1,y);
			 if (y==y1){
				printf("%c", 218);
			 }
			 else if(y==y2){
				printf("%c", 192);
			 }
			 else {
				printf("%c", 179);
			 }
		 }
		for(int x = x1; x <= x2; x++){
			if(x!=x1){
				 gotoxy(x,y1);
				 printf("%c", 196);
				 gotoxy(x,y2);
				 printf("%c", 196);
			}
		 }
		for(int y = y1; y <= y2; y++){
			 gotoxy(x2,y);
			if (y==y1){
				printf("%c", 191);
			 }
			 else if(y==y2){
				printf("%c", 217);
			 }
			 else {
				printf("%c", 179);
			 }
		 }
	}
}



