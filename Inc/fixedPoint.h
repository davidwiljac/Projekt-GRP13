/*
 * fixedPoint.h
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#ifndef FIXEDPOINT_H_
#define FIXEDPOINT_H_

#include "stdint.h"
#include "stdio.h"
#include "types.h"
#include "ansi.h"


uint32_t intToFp(uint16_t n);
int fpToInt(uint32_t fp);
vector_t scaleVector(vector_t vectorIn, uint32_t fpScalar);
uint32_t fpMultiply(uint32_t n, uint32_t m);
uint32_t fpDivide(uint32_t n, uint32_t m);
uint32_t fpAbs(uint32_t n);

#endif /* FIXEDPOINT_H_ */
