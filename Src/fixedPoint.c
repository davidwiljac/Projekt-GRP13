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

uint32_t fpMultiply(uint32_t n, uint32_t m){  //32 32 32
	n>>=8;
	m>>=8;
	uint32_t output = n*m;

	if ((n & 0x00800000) != 0) {
		output-=(2*0x00800000*m);
	}

	//output>>=8;//16


//	if(((n ^ m) & 0x80) != 0){
////		output=(~output)+1;
//		output|=0x80;
//	}
	return output;
}

uint32_t fpDivide(uint32_t n, uint32_t m){
    // Shift numerator to avoid overflow during multiplication
    uint64_t numerator = (long long)n << 16;

    // Perform the division and round to the nearest integer
    uint32_t result = (uint32_t)((numerator + (m / 2)) / m);

    return result;
}


vector_t scaleVector(vector_t vectorIn, uint32_t fpScalar){
	vector_t vectorOut;
	vectorOut.x=fpMultiply(vectorIn.x,fpScalar);
	vectorOut.y=fpMultiply(vectorIn.y,fpScalar);
	return vectorOut;
}


uint32_t fpAbs(uint32_t n){
	uint32_t output = n;
	if ((n & 0x80000000) != 0) {
			output=(~output)+1;
		}
	return output;
}

