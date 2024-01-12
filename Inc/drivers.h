/*
 * drivers.h
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#ifndef DRIVERS_H_
#define DRIVERS_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for 30010
#include "types.h"

uint32_t runtime;

// ^^^^ "uint32_t runtime" is our only global variable.
// It stores the time passed since the program started in centiseconds.
// This is very useful for joystick drivers  and
// keeping time for in game activities as well as for
// setting the frame rate.
// It first resets after around 1,36 years using uint32_t.


void initJoystick();
uint8_t centerIsPressed();
uint8_t upIsPressed();
uint8_t downIsPressed();
uint8_t leftIsPressed();
uint8_t rightIsPressed();

void I2C_init();
void I2C_Write(uint16_t address, uint8_t reg, uint8_t val);
uint8_t I2C_Read(uint16_t address, uint8_t reg, uint8_t* vals, uint8_t n);

void initTimer();
void TIM1_BRK_TIM15_IRQHandler(void);

void analogConfigPorts();
uint16_t readPotentiometer();

void initRGB();
void RGBColor(uint8_t color[]);

void writeToFlash(uint16_t data, uint32_t address);
uint16_t readFromFlash(uint32_t address);

void setFreq(uint16_t freq);
void initBuzzerPin();
#endif /* DRIVERS_H_ */
