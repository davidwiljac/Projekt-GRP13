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

// position_t 8.8 fixed point format
typedef struct {
	uint16_t x;
	uint16_t y;
}position_t;


// vector_t 8.8 fixed point format
typedef struct {
	uint16_t x;
	uint16_t y;
}vector_t;





//bullet_t
typedef struct {
	position_t position;
	position_t nextPosition;
	vector_t velocity;
}bullet_t;


//enemy_t
typedef struct {
	position_t position;
	position_t nextPosition;
	vector_t velocity;
	uint8_t firingRate;
} enemy_t ;

// bullet_node_t
typedef struct {
	bullet_t bullet;
	bullet_t* nextBullet;
}bullet_node_t;


//enemy_node_t
typedef struct {
	enemy_t enemy;
	enemy_t* nextEnemy;
} enemy_node_t;







//nuke_t
typedef struct {
	position_t position;
	position_t nextPosition;
	uint8_t isDeployed;
	uint8_t readyState; //(0=rød, 1=magenta, 2=gul, 3=grøn)
	uint8_t timeSinceLastActivation; //(i sekunder)
} nuke_t ;

//spaceShip_t
typedef struct {
	position_t position;
	position_t nextPosition;
	uint8_t numberOfParts;
	uint8_t firingRate;
	nuke_t nuke;
	uint8_t powerups;
} spaceship_t ;


//moon_t
typedef struct {
	position_t position;
	uint8_t mass;
}moon_t;


// gameState_t
typedef struct {
	bullet_node_t bulletLinkedList;
	enemy_node_t enemyLinkedList;
	moon_t* moons;
	spaceship_t spaceship;
	uint8_t cityLives;
	uint16_t score;
	uint8_t activeScreen;
	uint8_t menuSelected;
	uint8_t isDead;
	uint8_t difficulty;
} gameState_t ;


#endif /* TYPES_H_ */
