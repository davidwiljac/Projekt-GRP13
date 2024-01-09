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


uint32_t intToFp(uint16_t n);
int fpToInt(uint32_t fp);


#endif /* FIXEDPOINT_H_ */
