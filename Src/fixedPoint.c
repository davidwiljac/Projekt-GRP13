/*
 * fixedPoint.c
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#include "fixedPoint.h"

//Converts uint_t to fixed point 16.16 format type uint32_t
uint32_t intToFp(uint16_t n){
	uint32_t output = 0;
	output+=n;
	output<<=16;
	return output;
}

//Converts fixed point 16.16 format to normal integer and rounds correctly
int fpToInt(uint32_t fp){
	uint32_t in = fp;
	int output=0;
	fp+=32768; //32768 in 16.16 format is 0,5
	fp>>=16;
	output+=fp;
	if((in & 0x80000000)!=0) {
		output-=65536;
	}
	return output;

}

