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

	gotoxy(47,5); printf(" _____                 _ _             ___  _   _             _    ");
	gotoxy(47,6); printf("|  __ \\               (_) |           / _ \\| | | |           | |   ");
	gotoxy(47,7); printf("| |  \\/_ __ __ ___   ___| |_ _   _   / /_\\ \\ |_| |_ __ _  ___| | __");
	gotoxy(47,8); printf("| | __| '__/ _` \\ \\ / / | __| | | |  |  _  | __| __/ _` |/ __| |/ /");
	gotoxy(47,9); printf("| |_\\ \\ | | (_| |\\ V /| | |_| |_| |  | | | | |_| || (_| | (__|   < ");
	gotoxy(47,10); printf(" \\____/_|  \\__,_| \\_/ |_|\\__|\\__, |  \\_| |_/\\__|\\__\\__,_|\\___|_|\\_\\");
	gotoxy(47,11); printf("                              __/ |                                ");
    gotoxy(47,12); printf("                             |___/                                 ");

	drawButton(btnList[0]);
	drawButton(btnList[1]);
	drawButton(btnList[2]);
	drawBtnAsSelected(btnList[gameState->btnSelected]);
	gotoxy(73,35);
	printf("Highscore: %d", readFromFlash(0x0800F800));
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



