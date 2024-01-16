/*
 * dropperpower.c
 *
 *  Created on: 15 Jan 2024
 *      Author: Bivertical
 */

#include "dropperpower.h"
#include "types.h"
#define spawnPeriod 1500


void spawnDropper(gameState_t* gameState){
	if(runtime-gameState->dropper.lastseentime>=spawnPeriod){
		gameState->dropper.lastseentime=runtime;
		gameState->dropper.isvisible=1;
		position_t spawnPos = {intToFp(4), intToFp(5)*yScale};
		vector_t vel = {intToFp(1), intToFp(0)*yScale};
		gameState->dropper.position=spawnPos;
		gameState->dropper.nextposition=spawnPos;
		gameState->dropper.velocity=vel;
	}
}


void updateDropper(gameState_t* gameState){
	if(gameState->dropper.isvisible){

		gameState->dropper.nextposition.x=gameState->dropper.position.x+gameState->dropper.velocity.x;
		gameState->dropper.nextposition.y=gameState->dropper.position.y+gameState->dropper.velocity.y;

		if(fpToInt(gameState->dropper.nextposition.x)>=140){
			deleteDropper(fpToInt(gameState->dropper.position.x),fpToInt(gameState->dropper.position.y)/yScale);
			gameState->dropper.isvisible=0;
			gameState->dropper.lastseentime=runtime;
		}

	}
}

void conditionDropper(gameState_t* gameState){

	if(gameState->dropper.isvisible){
		deleteDropper(fpToInt(gameState->dropper.position.x),fpToInt(gameState->dropper.position.y)/yScale);
		drawDropper(gameState);
	}
	gameState->dropper.position=gameState->dropper.nextposition;
}

void deleteDropper(uint8_t X,uint8_t Y){
	gotoxy(X,Y);
	printf("       ");
	gotoxy(X,Y-1);
	printf("       ");
	gotoxy(X,Y+1);
	printf("       ");
}

