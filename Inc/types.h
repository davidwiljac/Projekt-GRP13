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


//bullet_t
typedef struct {
	position_t position;
	position_t nextPosition;
	vector_t velocity;
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
	uint8_t isDeployed; //(0 = not deployed, 1 = deployed)
	uint8_t readyState; //(0 = not ready, 1 = ready)
	uint8_t lastActivationTime; //(i centiSekunder)
} nuke_t ;

//spaceShip_t
typedef struct {
	position_t position;
	position_t nextPosition;
	uint8_t numberOfParts;
	uint8_t firingPeriod; //time in centiseconds between each shot
	uint8_t powerups;
	uint32_t lastShotTime;
	//nuke_t nuke; //skal uncommentes senere
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
	uint8_t keyboardDelay;
	char lastKeyPress;
} gameState_t ;


//button_t - (x,y) is point of top left corner
typedef struct {
	uint8_t x;
	uint8_t y;
	char* text;
} button_t;

#endif /* TYPES_H_ */
