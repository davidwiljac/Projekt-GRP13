/*
 * graphics.c
 *
 *  Created on: 8 Jan 2024
 *      Author: Bivertical
 */
#include "stdint.h"
#include "stdio.h"
#include "ansi.h"

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


void drawMoon(uint8_t X, uint8_t Y){
	// FX (51,17)
	gotoxy(X-1,Y+3);
	printf("_");
	gotoxy(X,Y+3);
	printf("_");
	gotoxy(X+1,Y+3);
	printf("_");
	gotoxy(X-2,Y+3);
	printf("(");
	gotoxy(X+2,Y+3);
	printf(")");

	gotoxy(X+3,Y+2);
	printf("_");
	gotoxy(X-3,Y+2);
	printf("_");
	gotoxy(X+4,Y+2);
	printf("(");
	gotoxy(X-4,Y+2);
	printf(")");

	gotoxy(X-5,Y+1);
	printf("(");
	gotoxy(X+5,Y+1);
	printf("(");
	gotoxy(X-6,Y);
	printf("(");
	gotoxy(X+6,Y);
	printf(")");

	gotoxy(X-5,Y-1);
	printf("(");
	gotoxy(X+5,Y-1);
	printf(")");
	gotoxy(X-4,Y-2);
	printf("(");
	gotoxy(X+4,Y-2);
	printf(")");

	gotoxy(X-3,Y-3);
	printf("_");
	gotoxy(X+3,Y-3);
	printf("_");
	gotoxy(X-2,Y-3);
	printf("(");
	gotoxy(X+2,Y-3);
	printf(")");

	gotoxy(X-1,Y-4);
	printf("_");
	gotoxy(X,Y-4);
	printf("_");
	gotoxy(X+1,Y-4);
	printf("_");

	gotoxy(X-2,Y);
	printf("O");
	gotoxy(X+1,Y+2);
	printf("o");
	gotoxy(X+3,Y-1);
	printf("O");



//	gotoxy(15,1);
//	printf("%c",219);
//	gotoxy(17,1);
//	printf("%c",219);
//	gotoxy(16,2);
//	printf("%c",223);
//	gotoxy(16,1);
//	printf("%c",220);
////	gotoxy(17,2);
////	printf("%c",223);
////	gotoxy(15,2);
////	printf("%c",223);
//
//	gotoxy(19,1);
//	printf("%c",219);
//	gotoxy(21,1);
//	printf("%c",219);
//	gotoxy(20,2);
//	printf("%c",223);
//	gotoxy(20,1);
//	printf("%c",220);
////	gotoxy(19,2);
////	printf("%c",223);
////	gotoxy(21,2);
////	printf("%c",223);
//
//	gotoxy(23,1);
//	printf("%c",219);
//	gotoxy(25,1);
//	printf("%c",219);
//	gotoxy(24,2);
//	printf("%c",223);
//	gotoxy(24,1);
//	printf("%c",220);
////	gotoxy(23,2);
////	printf("%c",223);
////	gotoxy(25,2);
////	printf("%c",223);


	//middle of the Moon
	//gotoxy(51,17);
	//printf("O");
}


void drawhearth(){
	fgcolor(1);
	gotoxy(15,1);
	printf("%c",219);
	gotoxy(17,1);
	printf("%c",219);
	gotoxy(16,2);
	printf("%c",223);
	gotoxy(16,1);
	printf("%c",220);


	gotoxy(19,1);
	printf("%c",219);
	gotoxy(21,1);
	printf("%c",219);
	gotoxy(20,2);
	printf("%c",223);
	gotoxy(20,1);
	printf("%c",220);


	gotoxy(23,1);
	printf("%c",219);
	gotoxy(25,1);
	printf("%c",219);
	gotoxy(24,2);
	printf("%c",223);
	gotoxy(24,1);
	printf("%c",220);
	fgcolor(15);





}


void drawEnemy(gameState_t* gameState){
	int isLastElement = 0;
	enemyNode_t* thisNode = gameState->enemyLL;

	while(1){
		if(thisNode->enemy->position->x != 0){
			gotoxy(fpToInt(thisNode->enemy->position->x), fpToInt(thisNode->enemy->position->y));
			//printf("%d %d", fpToInt(thisNode->enemy->position->x), fpToInt(thisNode->enemy->position->y));
			printf("  ");
			gotoxy(fpToInt(thisNode->enemy->nextPosition->x), fpToInt(thisNode->enemy->nextPosition->y));
			printf(":E");
			thisNode->enemy->position->x = thisNode->enemy->nextPosition->x;
			thisNode->enemy->position->y = thisNode->enemy->nextPosition->y;
		}
		if(thisNode->nextEnemyNode == 0){
			break;
		}
		thisNode = thisNode->nextEnemyNode;
	}
}

void drawBullet(){

}

void drawMe(uint8_t X, uint8_t Y){
	//middle 20,35
	gotoxy(X,Y);
	printf("%c",219);
	gotoxy(X-1,Y);
	printf("%c",220);
	gotoxy(X+1,Y);
	printf("%c",220);
	gotoxy(X-1,Y+1);
	printf("%c",223);
	gotoxy(X+1,Y+1);
	printf("%c",223);

	gotoxy(X,Y-1);
	printf("%c",179);
//186
	gotoxy(X-1,Y+2);
	printf("%c",176);
	gotoxy(X+1,Y+2);
	printf("%c",176);

//47 92


}

void drawCity();
