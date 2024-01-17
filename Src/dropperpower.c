/*
 * dropperpower.c
 *
 *  Created on: 15 Jan 2024
 *      Author: Bivertical
 */

#include "dropperpower.h"
#include "types.h"
#include "powerup.h"
#define spawnPeriod 1200


void spawndropper(gameState_t* gameState){
	if(runtime-gameState->dropper.lastseentime>=spawnPeriod){
		gameState->dropper.lastseentime=runtime;
		gameState->dropper.isvisible=1;
		position_t spawnPos = {intToFp(4), intToFp(5)*yScale};
		vector_t vel = {intToFp(1), intToFp(0)*yScale};
		gameState->dropper.position=spawnPos;
		gameState->dropper.nextposition=spawnPos;
		gameState->dropper.velocity=vel;
		gameState->dropper.randomX=-1;
		if(!xValIsValid(gameState->dropper.randomX,6)){
			gameState->dropper.randomX=(rand() % 139);
		}
	}
}


void updatedropper(gameState_t* gameState){
	if(gameState->dropper.isvisible){

		gameState->dropper.nextposition.x=gameState->dropper.position.x+gameState->dropper.velocity.x;
		gameState->dropper.nextposition.y=gameState->dropper.position.y+gameState->dropper.velocity.y;
		if(fpToInt(gameState->dropper.position.x) >= gameState->dropper.randomX && !gameState->powerup.isVisible){

			spawnPowerup(gameState);

		}

		if(fpToInt(gameState->dropper.nextposition.x)>=139){
			deletedropper(fpToInt(gameState->dropper.position.x),fpToInt(gameState->dropper.position.y)/yScale);
			gameState->dropper.isvisible=0;
			gameState->dropper.lastseentime=runtime;
		}
	}
}

void conditiondropper(gameState_t* gameState){

	if(gameState->dropper.isvisible){
		deletedropper(fpToInt(gameState->dropper.position.x),fpToInt(gameState->dropper.position.y)/yScale);
		drawdropper(gameState);
	}
	gameState->dropper.position=gameState->dropper.nextposition;
}

void deletedropper(uint8_t X,uint8_t Y){
	gotoxy(X,Y);
	printf("       ");
	gotoxy(X,Y-1);
	printf("       ");
	gotoxy(X,Y+1);
	printf("       ");
}


