/*
 * types.h
 *
 *  Created on: 6. jan. 2024
 *      Author: Loren
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "stdint.h"
#include "stdio.h"

// position_t 16.16 fixed point format
typedef struct {
	uint32_t x;
	uint32_t y;
}position_t;


// vector_t 16.16 fixed point format
typedef struct {
	uint32_t x;
	uint32_t y;
}vector_t;


//enemy_t
typedef struct {
	position_t* position;
	position_t* nextPosition;
	vector_t* velocity;
	uint8_t firingRate;
	uint32_t lastShotTime;
} enemy_t ;

//powerup_t
typedef struct {
	uint8_t isVisible;
	position_t position;
	position_t nextPosition;
	vector_t velocity;
	uint32_t lastUseTime;
} powerup_t ;


//bullet_t
typedef struct {
	position_t position;
	position_t nextPosition;
	vector_t velocity;
	uint32_t distanceToMoon; //(estimate) 16.16 fixed point
}bullet_t;


typedef struct bulletNode_t bulletNode_t;

// bullet_node_t
struct bulletNode_t {
	bullet_t bullet;
	bulletNode_t * nextBulletAddress;
};

typedef struct enemyNode_t enemyNode_t;

//enemy_node_t
struct enemyNode_t {
	enemy_t* enemy;
	enemyNode_t* nextEnemyNode;
};


//nuke_t
typedef struct {
	position_t position;
	position_t nextPosition;
	vector_t velocity;
	uint8_t isDeployed; //(0 = not deployed, 1 = deployed)
	uint8_t readyState; //(0 = not ready, 1 = ready)
	uint32_t lastDetonationTime;
	uint8_t circleClear;
	uint32_t lastActivationTime; //(i centiSekunder)
} nuke_t ;

//spaceShip_t
typedef struct {
	position_t prePosition;
	position_t position;
	position_t nextPosition;
	uint8_t numberOfParts;
	uint8_t powerups;
} spaceship_t ;


//moon_t
typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t mass;
}moon_t;


// gameState_t
typedef struct {
	bulletNode_t* bulletLL;
	enemyNode_t* enemyLL;
	uint32_t nextEnemySpawn;
	moon_t moon;
	spaceship_t spaceship;
	nuke_t* nuke;
	uint8_t cityLives;
	uint16_t score;
	uint8_t lastScreen; //For the purpose of bossKey
	uint8_t activeScreen;  // 0=menu screen, 1= game screen, 2=help screen, 3=game over, 4 = bossMode
	uint8_t bossMode; //0 = Off, 1 = On;
	uint8_t btnSelected;  // 0=start game, 1=difficulty, 2=help
	uint8_t isDead;
	uint8_t difficulty; // 0=easy, 1=medium, 2=hard
	int8_t direction;
	uint32_t lastKeyPressTime;
	char lastKeyPress;
	powerup_t powerup;

	uint8_t soundToPlay;
	uint8_t lastSoundToPlay;
	uint8_t soundIndex;
	uint32_t soundTime;
} gameState_t ;


//button_t - (x,y) is point of top left corner
typedef struct {
	uint8_t x;
	uint8_t y;
	char* text;
} button_t;

typedef struct {
	uint16_t frequency; //In Hz
	uint16_t duration; //In centiseconds
} sound_t;
#endif /* TYPES_H_ */
