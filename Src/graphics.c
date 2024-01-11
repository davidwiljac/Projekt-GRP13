/*
 * graphics.c
 *
 *  Created on: 8 Jan 2024
 *      Author: Bivertical
 */
#include "graphics.h"

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


void drawhearth(gameState_t* gameState){
	fgcolor(1);
	gotoxy(15,1);
	printf("           ");
	gotoxy(15,2);
	printf("           ");

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

//void hearth(){
//	fgcolor(1);
//	gotoxy(15,2);
//	printf("%c",219);
//
//
//}

//void Moongravity(){
//	let mover;
//	let attractor;
//
//	xyPOS = drawMoon(51,17);
//	BulletPOS
//}


void drawEnemy(gameState_t* gameState){
	int isLastElement = 0;
	enemyNode_t* thisNode = gameState->enemyLL;

	while(thisNode != NULL){
		gotoxy(fpToInt(thisNode->enemy->position->x), fpToInt(thisNode->enemy->position->y));
		printf("  ");
		gotoxy(fpToInt(thisNode->enemy->nextPosition->x), fpToInt(thisNode->enemy->nextPosition->y));
		printf(":E");
		thisNode->enemy->position->x = thisNode->enemy->nextPosition->x;
		thisNode->enemy->position->y = thisNode->enemy->nextPosition->y;
		thisNode = thisNode->nextEnemyNode;
	}
}

void drawBullet(){

}

<<<<<<< Updated upstream
void drawMe(){

=======
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
>>>>>>> Stashed changes
}
