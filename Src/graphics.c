/*
 * graphics.c
 *
 *  Created on: 8 Jan 2024
 *      Author: Bivertical
 */
#include "stdint.h"
#include "stdio.h"
#include "ansi.h"
#include "graphics.h"

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
	Y /= yScale;
//	gotoxy(X,Y);
//	printf("X");
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

	//middle of the Moon
	//gotoxy(51,17);
	//printf("O");
}


void drawhearth(gameState_t* gameState){
	gotoxy(15,1);
	printf("           ");
	gotoxy(15,2);
	printf("           ");
	fgcolor(1);

	if(gameState->cityLives >= 1){
		gotoxy(15,1);
		printf("%c",219);
		gotoxy(17,1);
		printf("%c",219);
		gotoxy(16,2);
		printf("%c",223);
		gotoxy(16,1);
		printf("%c",220);
	}
	if(gameState->cityLives >= 2){
		gotoxy(19,1);
		printf("%c",219);
		gotoxy(21,1);
		printf("%c",219);
		gotoxy(20,2);
		printf("%c",223);
		gotoxy(20,1);
		printf("%c",220);

	}
	if(gameState->cityLives >= 3){
		gotoxy(23,1);
		printf("%c",219);
		gotoxy(25,1);
		printf("%c",219);
		gotoxy(24,2);
		printf("%c",223);
		gotoxy(24,1);
		printf("%c",220);
	}
	fgcolor(15);
}
	//const double g=9.81; //gravitational acceleration (m/s^2)
	//const double dt=0.01; //time step (s)
	//const double deg_to_rad = 3.14159265359 / 180; // conversion factor from degrees to radians



void drawEnemy(gameState_t* gameState){
	//int isLastElement = 0;
	enemyNode_t* thisNode = gameState->enemyLL;

	while(thisNode != NULL){
		gotoxy(fpToInt(thisNode->enemy->position->x), fpToInt(thisNode->enemy->position->y)/yScale);
		printf("       ");
		gotoxy(fpToInt(thisNode->enemy->position->x), (fpToInt(thisNode->enemy->position->y) + 1 * yScale)/yScale);
		printf("       ");

		gotoxy(fpToInt(thisNode->enemy->nextPosition->x), fpToInt(thisNode->enemy->nextPosition->y)/yScale);
		printf("  o o  ");
		gotoxy(fpToInt(thisNode->enemy->nextPosition->x), (fpToInt(thisNode->enemy->nextPosition->y) + 1 * yScale)/yScale);
		printf("%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 187);

		thisNode->enemy->position->x = thisNode->enemy->nextPosition->x;
		thisNode->enemy->position->y = thisNode->enemy->nextPosition->y;
		thisNode = thisNode->nextEnemyNode;
	}
}
// ^ ^ ^ ^
// -------

void drawBullet(uint8_t X, uint8_t Y){
	gotoxy(X,Y);
	printf("%c",127);
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

void drawCity(){

	gotoxy(14,44);
	printf("%c",219);

	gotoxy(16,44);
	printf("%c",219);

	gotoxy(17,44);
	printf("%c",219);
	gotoxy(17,43);
	printf("%c",219);

	gotoxy(19,44);
	printf("%c",220);

	gotoxy(21,44);
	printf("%c",219);

	gotoxy(23,44);
	printf("%c",219);
	gotoxy(23,43);
	printf("%c",220);

	gotoxy(25,44);
	printf("%c",219);
	gotoxy(25,43);
	printf("%c",219);
	gotoxy(25,42);
	printf("%c",219);

	gotoxy(27,44);
	printf("%c",219);
	gotoxy(27,43);
	printf("%c",220);

	gotoxy(28,44);
	printf("%c",219);

	gotoxy(36,44);
	printf("%c",219);
	gotoxy(36,43);
	printf("%c",219);

	gotoxy(37,44);
	printf("%c",219);

	gotoxy(38,44);
	printf("%c",220);

	gotoxy(40,44);
	printf("%c",219);
	gotoxy(40,43);
	printf("%c",219);

	gotoxy(41,43);
	printf("%c",205);

	gotoxy(42,44);
	printf("%c",219);
	gotoxy(42,43);
	printf("%c",219);

	gotoxy(45,44);
	printf("%c",186);

	gotoxy(47,44);
	printf("%c",220);

	gotoxy(55,44);
	printf("%c",219);
	gotoxy(55,43);
	printf("%c",220);

	gotoxy(58,44);
	printf("%c",219);
	gotoxy(58,43);
	printf("%c",219);
	gotoxy(58,42);
	printf("%c",220);

	gotoxy(59,44);
	printf("%c",219);
	gotoxy(59,43);
	printf("%c",220);

	gotoxy(60,44);
	printf("%c",219);

	gotoxy(61,44);
	printf("%c",219);
	gotoxy(61,43);
	printf("%c",219);

	gotoxy(63,44);
	printf("%c",219);

	gotoxy(64,44);
	printf("%c",220);

	gotoxy(65,44);
	printf("%c",219);

	gotoxy(67,44);
	printf("%c",219);
	gotoxy(67,43);
	printf("%c",219);
	gotoxy(67,42);
	printf("%c",219);

	gotoxy(69,44);
	printf("%c",219);
	gotoxy(69,43);
	printf("%c",219);
	gotoxy(69,42);
	printf("%c",219);

	gotoxy(71,44);
	printf("%c",219);
	gotoxy(71,43);
	printf("%c",219);
	gotoxy(71,42);
	printf("%c",219);

	gotoxy(73,44);
	printf("%c",219);
	gotoxy(73,43);
	printf("%c",219);

	gotoxy(74,44);
	printf("%c",219);

	gotoxy(76,44);
	printf("%c",219);

	gotoxy(77,44);
	printf("%c",219);
	gotoxy(77,43);
	printf("%c",219);

	gotoxy(79,44);
	printf("%c",219);
	gotoxy(79,44);
	printf("%c",220);

	gotoxy(81,44);
	printf("%c",219);
	gotoxy(81,43);
	printf("%c",219);

	gotoxy(82,44);
	printf("%c",219);

	gotoxy(85,44);
	printf("%c",219);
	gotoxy(85,43);
	printf("%c",219);
	gotoxy(85,42);
	printf("%c",220);

	gotoxy(86,44);
	printf("%c",219);

	gotoxy(87,44);
	printf("%c",220);

	gotoxy(88,44);
	printf("%c",219);
	gotoxy(88,43);
	printf("%c",220);

	gotoxy(93,44);
	printf("%c",219);

	gotoxy(94,44);
	printf("%c",219);
	gotoxy(94,43);
	printf("%c",220);

	gotoxy(95,44);
	printf("%c",220);

	gotoxy(96,44);
	printf("%c",219);

	gotoxy(98,44);
	printf("%c",219);
	gotoxy(98,43);
	printf("%c",220);

	gotoxy(99,44);
	printf("%c",219);

	gotoxy(103,44);
	printf("%c",219);

	gotoxy(104,44);
	printf("%c",220);

	gotoxy(107,44);
	printf("%c",219);

	gotoxy(108,44);
	printf("%c",219);
	gotoxy(108,43);
	printf("%c",219);

	gotoxy(109,44);
	printf("%c",220);

	gotoxy(112,44);
	printf("%c",219);

	gotoxy(113,44);
	printf("%c",220);

	gotoxy(114,44);
	printf("%c",219);
	gotoxy(114,43);
	printf("%c",219);

	gotoxy(115,44);
	printf("%c",219);

	gotoxy(120,44);
	printf("%c",47);
	gotoxy(121,43);
	printf("%c",47);
	gotoxy(122,43);
	printf("%c",223);
	gotoxy(122,42);
	printf("%c",168);
	gotoxy(123,43);
	printf("%c",92);
	gotoxy(124,44);
	printf("%c",92);

	gotoxy(127,44);
	printf("%c",219);
	gotoxy(127,43);
	printf("%c",219);
	gotoxy(127,42);
	printf("%c",219);

	gotoxy(129,44);
	printf("%c",219);
	gotoxy(129,43);
	printf("%c",220);

	gotoxy(130,44);
	printf("%c",219);

	gotoxy(131,44);
	printf("%c",220);

	gotoxy(132,44);
	printf("%c",219);

	gotoxy(133,44);
	printf("%c",219);
	gotoxy(133,43);
	printf("%c",219);

	gotoxy(134,44);
	printf("%c",219);

	gotoxy(135,44);
	printf("%c",220);

	gotoxy(137,44);
	printf("%c",220);

	gotoxy(139,44);
	printf("%c",220);

	gotoxy(141,44);
	printf("%c",219);

	gotoxy(142,44);
	printf("%c",220);
}
