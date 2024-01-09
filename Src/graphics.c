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



	gotoxy(15,1);
	printf("%c",219);
	gotoxy(17,1);
	printf("%c",219);
	gotoxy(16,2);
	printf("%c",223);
	gotoxy(16,1);
	printf("%c",220);
//	gotoxy(17,2);
//	printf("%c",223);
//	gotoxy(15,2);
//	printf("%c",223);

	gotoxy(19,1);
	printf("%c",219);
	gotoxy(21,1);
	printf("%c",219);
	gotoxy(20,2);
	printf("%c",223);
	gotoxy(20,1);
	printf("%c",220);
//	gotoxy(19,2);
//	printf("%c",223);
//	gotoxy(21,2);
//	printf("%c",223);

	gotoxy(23,1);
	printf("%c",219);
	gotoxy(25,1);
	printf("%c",219);
	gotoxy(24,2);
	printf("%c",223);
	gotoxy(24,1);
	printf("%c",220);
//	gotoxy(23,2);
//	printf("%c",223);
//	gotoxy(25,2);
//	printf("%c",223);





	//middle of the Moon
	//gotoxy(51,17);
	//printf("O");
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

void drawMe(){

}
