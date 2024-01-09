/*
 * MoonGravity.c
 *
 *  Created on: 9 Jan 2024
 *      Author: Bivertical
 */

#include "stdint.h"
#include "stdio.h"
#include "ansi.h"
#include "graphics.h"

//typedef struct{
//	uint8_t x;
//	uint8_t y;
//	uint8_t velocity_x;
//	uint8_t velocity_y;
//}bullet;
//
//
//void applyGravity(bullet *bullet, drawMoon *drawMoon){
//	float gravity_constant = 9.81;
//	//calculate distance between moon and bullet
//	float dx = drawMoon->x - bullet->x;
//	float dy = drawMoon->y - bullet->y;
//	float distance_squarred = dx * dx + dy * dy;
//	float distance = sqrt(distance_squarred);
//
//	if (distance > 0) { //apply gravitational force to alter bullet's velocity
//		float force_magnitude = gravity_constant / distance_squarred;
//		float force_x = force_magnitude * (dx/distance);
//		float force_y = force_magnitude * (dy/distance);
//
//		bullet->velocity_x+=force_x;
//		bullet->velocity_y+=force_y;
//	}
//
//	for (int i=0; i<10 ;++1){
//		applyGravity(&bullet, &drawMoon);
//
//		bullet.x += bullet.velocity_x;
//		bullet.y += bullet.velocity_y;
//	}
//}
