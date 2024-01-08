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


uint16_t intToFp(uint8_t n);
uint8_t fpToInt(uint16_t fp);


#endif /* FIXEDPOINT_H_ */
