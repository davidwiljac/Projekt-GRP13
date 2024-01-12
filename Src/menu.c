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

void drawWindow(uint8_t isGameWindow){
	drawBox(1,1,screenWidth, screenHeight,0);
	if(isGameWindow){//bottom line is deleted
		gotoxy(1,screenHeight-1);
		printf(" ");
		gotoxy(1,screenHeight-2);
		printf(" ");
		gotoxy(1,screenHeight-3);
		printf(" ");
		gotoxy(screenWidth,screenHeight-1);
		printf(" ");
		gotoxy(screenWidth,screenHeight-2);
		printf(" ");
		gotoxy(screenWidth,screenHeight-3);
		printf(" ");
		for(int x = 1; x<screenWidth+1;x++){
			gotoxy(x, screenHeight);
			printf(" ");

		}
	}
}



