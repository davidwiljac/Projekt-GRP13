/*
 * fixedPoint.c
 *
 *  Created on: 8. jan. 2024
 *      Author: Loren
 */

#include "fixedPoint.h"

/**
  * @brief  Converts uint_t to fixed point 16.16 format type uint32_t
  * @param  n: an unsigned 16 bit integer
  * @retval a 16.16 32-bit fixed point number in 2' complement
  */
uint32_t intToFp(uint16_t n){
	uint32_t output = 0;
	output+=n;
	output<<=16;
	return output;
}

/**
  * @brief  Converts fixed point 16.16 format to normal integer and rounds correctly
  * @param  fp: a 16.16 32-bit fixed point number in 2's complement
  * @retval an unsigned 16 bit integer
  */
uint16_t fpToInt(uint32_t fp){
	uint16_t output=0;
	fp+=32768; //32768 in 16.16 format is 0,5
	fp>>=16;
	output+=fp;
	return output;

}

/**
  * @brief  Multiplies 2 fixed-point values
  * @param  n: first number, m: second number (must be non-negative)
  * @retval a 16.16 32-bit fixed point number in 2' complement
  */
uint32_t fpMultiply(uint32_t n, uint32_t m){  //32 32 32
	n>>=8;
	m>>=8;
	uint32_t output = n*m;
	if ((n & 0x00800000) != 0) {
		output-=(2*0x00800000*m);
	}
	return output;
}

/**
  * @brief  Divides 2 fixed-point values TODO: REF (fra ChatGPT -modificeret)
  * @param  n: first number, m: second number
  * @retval a 16.16 32-bit fixed point number in 2' complement
  */
uint32_t fpDivide(uint32_t n, uint32_t m){
    uint64_t numerator = 0;
    numerator+=n;
    numerator <<= 16;
    uint32_t output = (uint32_t)((numerator + (m / 2)) / m);
    return output;
}

/**
  * @brief  Scale a vector with a given factor
  * @param  vectorIn: The vector to be scaled, fpScalar: The amount to scale (must be non-negative)
  * @retval The scaled vector
  */
vector_t scaleVector(vector_t vectorIn, uint32_t fpScalar){
	vector_t vectorOut;
	vectorOut.x=fpMultiply(vectorIn.x,fpScalar);
	vectorOut.y=fpMultiply(vectorIn.y,fpScalar);
	return vectorOut;
}

/**
  * @brief Gives the absolute value of a fixed point value
  * @param  n: the 16.16 formatted fixed point number to get the abs of
  * @retval A positive 16.16 number
  */
uint32_t fpAbs(uint32_t n){
	uint32_t output = n;
	if ((n & 0x80000000) != 0) {
			output=(~output)+1;
		}
	return output;
}

