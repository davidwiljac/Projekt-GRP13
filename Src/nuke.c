/*
 * nuke.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */
#include"nuke.h"

void chargeNuke(gameState_t* gameState){
	if(gameState->nuke->readyState == 1){
		return;
	}
	uint8_t color[] = {1,0,0};
	if(runtime - gameState->nuke->lastActivationTime > 500){
		color[0] = 1;
		color[1] = 0;
		color[2] = 1;
		RGBColor(color);
	}
	if(runtime - gameState->nuke->lastActivationTime > 1000){
		color[0] = 1;
		color[1] = 1;
		color[2] = 0;
		RGBColor(color);
	}
	if(runtime - gameState->nuke->lastActivationTime > 1500){
		color[0] = 0;
		color[1] = 1;
		color[2] = 0;
		RGBColor(color);
		gameState->nuke->readyState = 1;
	}
}

void shootNuke(gameState_t* gameState){

}

void updateNuke(gameState_t* gameState){
	chargeNuke(gameState);

}
