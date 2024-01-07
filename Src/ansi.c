/*
 * ansi.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#define ESC 0x1B
#include "ansi.h"

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

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr(){ //clears screen
    printf("%c[H", ESC);
    printf("%c[J", ESC);
}

void clreol(){ //clears rest of line
//    printf("%c[1F", ESC); //move to start of line
    printf("%c[2K", ESC); //Clears line
}

//Sends cursor to the given coordinate
void gotoxy(int x, int y){
    printf("%c[%d;%dH", ESC, y, x);
}


//Starts underline or removes it depending on 'underline_on'
void underline(int underline_on){
    if(underline_on){
   	 printf("%c[04m", ESC);
    }else{
   	 printf("%c[24m", ESC);
    }
}

//Starts blink or removes it depending on 'blink_on'
void blink(int blink_on){
    if(blink_on){
   	 printf("%c[05m", ESC);
    }else{
   	 printf("%c[25m", ESC);
    }
}


//Starts inverse or removes it depending on 'inverse_on'
void inverse(int inverse_on){
    if(inverse_on){
   	 printf("%c[07m", ESC);
    }else{
   	 printf("%c[27m", ESC);
    }
}



void drawBox(int x1, int y1, int x2, int y2, int style) { //style: 0=thin, 1=bold
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



