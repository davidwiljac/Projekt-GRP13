/*
 * sound.c
 *
 *  Created on: 12. jan. 2024
 *      Author: Loren
 */

#include "sound.h"

const sound_t sounds[][4] = {
		{},
		{{1000,1},{0,0}}, //Bullet shot
		{{400,5},{0,5},{400,5},{0,0}}, //Nuke ready
		{{1046,2},{1318,2}, {0,0}}, //powerup taken
		{{300,5},{0,0}} //lost spaceship part
};

/**
  * @brief  Checks if a sound should be played, and does if so
  * @param  gameState: the current state of the game
  * @retval None
  */
void playSound(gameState_t* gameState){
	//Checks if a sound should play
	if(gameState->soundToPlay == 0) return;

	//Checks if the sound has changed
	if(gameState->soundToPlay != gameState->lastSoundToPlay){
		gameState->soundIndex = 0;
	}

	//Checks if the current tone has completed
	if(runtime - gameState->soundTime > sounds[gameState->soundToPlay][gameState->soundIndex-1].duration){
		setFreq(sounds[gameState->soundToPlay][gameState->soundIndex].frequency);
		toggleBuzzer(1);


		//If it reaches {0,0} stop playing any sound
		if(sounds[gameState->soundToPlay][gameState->soundIndex].duration == 0 &&
				sounds[gameState->soundToPlay][gameState->soundIndex].frequency == 0){
			toggleBuzzer(0);
			gameState->soundToPlay = 0;
			gameState->soundIndex = 0;
		}else{
			gameState->soundIndex++;
			gameState->soundTime = runtime;
		}
	}
	gameState->lastSoundToPlay = gameState->soundToPlay;
}
