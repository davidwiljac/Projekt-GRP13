/*
 * linkedList.h
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "types.h"
#include "fixedPoint.h"
#include "ansi.h"
#include <stdio.h>
#include <stdlib.h>

void appendBullet(bulletNode_t** head, bullet_t bullet);
bulletNode_t* createBulletNode(bullet_t bullet);

#endif /* LINKEDLIST_H_ */
