#include "menu.h"

/**
  * @brief  Draws a button to the screen
  * @param  btn: the button to draw
  * @retval None
  */
void drawButton(button_t btn){
	int strLength = (int)strlen(btn.text);
	drawBox(btn.x, btn.y, btn.x+strLength+5, btn.y+2, 0);
	gotoxy(btn.x+3, btn.y+1);
	printf(btn.text);
}

/**
  * @brief  Draws a button that has been selected to the screen
  * @param  btn: the button to draw
  * @retval None
  */
void drawBtnAsSelected(button_t btn){
	int strLength = (int)strlen(btn.text);
	drawBox(btn.x, btn.y, btn.x+strLength+5, btn.y+2, 1);
}

/**
  * @brief  Draw a button that was selected that aren't any more
  * @param  btn: the button to draw
  * @retval None
  */
void drawBtnAsDeselected(button_t btn){
	int strLength = (int)strlen(btn.text);
	drawBox(btn.x, btn.y, btn.x+strLength+5, btn.y+2, 0);
}

/**
  * @brief  Draws the entire main menu
  * @param  btnList: A list of buttons to draw, gameState: the current state of the game
  * @retval None
  */
void drawMenuScreen(button_t btnList[], gameState_t* gameState){

	drawWindow(0);
	drawbackground(); // stars in background
	drawMoon(gameState->moon.x, gameState->moon.y);

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

/**
  * @brief  Draws the help screen
  * @param  None
  * @retval None
  */
void drawHelpScreen(){
	gotoxy(70,5);
	printf("HELP SCREEN");
	uint16_t x = 10;
	uint16_t y = 10;
	gotoxy(x,y);
	printf("Styr din rum skib ved at dreje det venstre potentiometer frem og tilbage");
	gotoxy(x+=24, y+=2);
	printf("<-----     ----->");
	drawMe(x+=8,y);

	gotoxy(x-=32, y+=3);
	printf("Rumvaeserne vil prove at odelaegge din by. Hver gang de rammer den mister du et liv!");
	gotoxy(x, ++y);
	printf("  o o     o o     o o     o o  ");
	gotoxy(x, ++y);
	printf("%c%c%c%c%c%c%c %c%c%c%c%c%c%c %c%c%c%c%c%c%c %c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 187, 201, 205, 205, 205, 205, 205, 187, 201, 205, 205, 205, 205, 205, 187, 201, 205, 205, 205, 205, 205, 187);

	gotoxy(x, y+=3);
	printf("Er du ved at blive overvaeldet, kan du bruge din nuke.");
	gotoxy(x,++y);
	printf("Se pa LED'en hvornar den er klar");
	gotoxy(x,++y);
	fgcolor(1);
	printf("%c", 219);
	fgcolor(13);
	printf("%c", 219);
	fgcolor(11);
	printf("%c", 219);
	fgcolor(2);
	printf("%c", 219);
	fgcolor(15);

	gotoxy(x,y+=2);
	printf("Nar din nuke er klar dasker du blot til boardet for at sende den afted. Nar den er sendt afsted dasker du igen for at detonere den");
	gotoxy(x,++y);
	printf("  |  ");
	gotoxy(x,++y);
	printf("- o -");
	gotoxy(x,++y);
	printf(" / %c ", 92);

	gotoxy(x, y+=2);
	printf("Har du brug for hjaelp kan du samle powerups op. De giver dig enten flere rumdele, eller slukker fjendernes kanoner.");
	gotoxy(x, ++y);
	printf("Men pas pa bade dine egne og fjendens kugler kan odelaegge dine ekstra dele");
	drawBox(x, ++y, x+4, y+2, 1);
	gotoxy(x+2, y+1);
	printf("$");

	gotoxy(x, y+=4);
	printf("Har du brug for at skjule spillet, trykker du blot pa 'f', sa bliver spillet til en masse c-kode.");
}

/**
  * @brief  Draws the outer bounds
  * @param  isGameWindow: 1 = deletes bottom layer
  * @retval None
  */
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



