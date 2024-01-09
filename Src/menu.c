/*
 * menu.c
 *
 *  Created on: 7. jan. 2024
 *      Author: Loren
 */

#include "menu.h"




void drawButton(button_t btn){
	int strLength = (int)strlen(btn.text);
	drawBox(btn.x, btn.y, btn.x+strLength+5, btn.y+2, 0);
	gotoxy(btn.x+3, btn.y+1);
	printf(btn.text);
}

void drawBtnAsSelected(button_t btn){
	int strLength = (int)strlen(btn.text);
	drawBox(btn.x, btn.y, btn.x+strLength+5, btn.y+2, 1);
}

void drawBtnAsDeselected(button_t btn){
	int strLength = (int)strlen(btn.text);
	drawBox(btn.x, btn.y, btn.x+strLength+5, btn.y+2, 0);
}

void drawMenuScreen(button_t btnList[], gameState_t* gameState){
	drawButton(btnList[0]);
	drawButton(btnList[1]);
	drawButton(btnList[2]);
	drawBtnAsSelected(btnList[gameState->btnSelected]);
}


void drawHelpScreen(){
	gotoxy(70,5);
	printf("HELP SCREEN");
	gotoxy(60,7);
	printf("Tag dig dog sammen mand!");

}

void drawWindow(){
	drawBox(1,1,screenWidth, screenHeight,0);
}

void drawbackground(){
	gotoxy(55,35);
	printf("*");
	gotoxy(63,27);
	printf("*");
	gotoxy(10,15);
	printf("*");
	gotoxy(20,40);
	printf("%c",43);

	gotoxy(155,37);
	printf("*");
	gotoxy(110,28);
	printf("*");
	gotoxy(95,13);
	printf("*");
	gotoxy(130,19);
	printf("%c",43);

	gotoxy(5,27);
	printf("*");
	gotoxy(6,5);
	printf("*");
	gotoxy(13,13);
	printf("*");
	gotoxy(60,7);
	printf("%c",43);

	gotoxy(140,3);
	printf("*");
	gotoxy(120,5);
	printf("*");
	gotoxy(110,7);
	printf("*");
	gotoxy(70,30);
	printf("%c",43);

	gotoxy(135,33);
	printf("*");
	gotoxy(123,36);
	printf("*");
	gotoxy(138,40);
	printf("*");
	gotoxy(127,25);
	printf("%c",43);

	gotoxy(105,32);
	printf("%c",42);
	gotoxy(106,33);
	printf("%c",92);
	gotoxy(107,34);
	printf("%c",92);

	gotoxy(23,15);
	printf("*");
	gotoxy(37,21);
	printf("*");
	gotoxy(26,24);
	printf("*");
	gotoxy(30,29);
	printf("%c",43);

	gotoxy(25,6);
	printf("*");
	gotoxy(39,7);
	printf("*");
	gotoxy(41,3);
	printf("*");
	gotoxy(75,10);
	printf("%c",43);

	gotoxy(100,20);
	printf("%c",197);
	gotoxy(135,12);
	printf("%c",197);
	gotoxy(30,5);
	printf("%c",197);
}

