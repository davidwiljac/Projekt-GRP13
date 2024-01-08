/*
 * fixedPoint.c
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#include "fixedPoint.h"

//Converts normal uint_t to fixed point 8.8 format with type uint16_t
uint16_t intToFp(uint8_t n){
	uint16_t output = 0;
	output+=n;
	output<<=8;
	return output;
}

//Converts fixed point 8.8 format to normal integer and rounds correctly
uint8_t fpToInt(uint16_t fp){
	uint8_t output=0;
	fp+=128; //128 in 8.8 format is 0,5
	fp>>=8;
	output+=fp;
	return output;

}

