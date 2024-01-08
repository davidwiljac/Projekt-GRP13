/*
 * drivers.c
 *
 *  Created on: 6. jan. 2024
 *      Author: david
 */

#include"drivers.h"
#define btnDelay 30 //centisekunder


//JOYSTICK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

uint32_t centerPrevPressed = 0;
uint32_t upPrevPressed = 0;
uint32_t downPrevPressed = 0;
uint32_t leftPrevPressed = 0;
uint32_t rightPrevPressed = 0;

void initJoystick(){
	// Enable clock for GPIO Port A, B, C
	 RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
	 RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
	 RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

	//CENTER
	 GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	 GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	 //Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	 GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	 GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	 //	 No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	 //UP
	 GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	 GPIOA->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	 GPIOA->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	 GPIOA->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -

	 //down
	 GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	 GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	 GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	 GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -

	 //left
	 GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	 GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	 GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	 GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -

	 //right
	 GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	 GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	 GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	 GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -

}



uint8_t centerIsPressed(){
	 if(((GPIOB->IDR & (0x0001 << 5))!=0 )&& (runtime-centerPrevPressed>btnDelay)){
		 centerPrevPressed=runtime;
		 return 1;
	 } else {
		 if((GPIOB->IDR & (0x0001 << 5))==0){
			 centerPrevPressed=runtime-btnDelay;
		 }
		 return 0;
	 }
}

uint8_t upIsPressed(){
		 if(((GPIOA->IDR & (0x0001 << 4))!=0) && (runtime-upPrevPressed>btnDelay)){
			 upPrevPressed = runtime;
			 return 1;
		 } else {
			 if((GPIOA->IDR & (0x0001 << 4))==0){
				 upPrevPressed=runtime-btnDelay;
			 }
			 return 0;
		 }
	 }

uint8_t downIsPressed(){
		 if(((GPIOB->IDR & (0x0001 << 0))!=0)&& (runtime-downPrevPressed>btnDelay)){
			 downPrevPressed = runtime;
			 return 1;
		 } else {
			 if((GPIOB->IDR & (0x0001 << 0))==0){
				 downPrevPressed=runtime-btnDelay;
			 }
			 return 0;
		 }
	 }

uint8_t leftIsPressed(){
		 if(((GPIOC->IDR & (0x0001 << 1))!=0)&& (runtime-leftPrevPressed>btnDelay)){
			 leftPrevPressed = runtime;
			 return 1;
		 } else {
			 if((GPIOC->IDR & (0x0001 << 1))==0){
				 leftPrevPressed=runtime-btnDelay;
			 }
			 return 0;
		 }
	 }

uint8_t rightIsPressed(){
		 if(((GPIOC->IDR & (0x0001 << 0))!=0)&& (runtime-rightPrevPressed>btnDelay)){
			 rightPrevPressed = runtime;
			 return 1;
		 } else {
			 if((GPIOC->IDR & (0x0001 << 0))==0){
				 rightPrevPressed=runtime-btnDelay;
			 }
			 return 0;
		 }
	 }

// JOYSTICK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// TIMER vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

void initTimer(){ //period = 0,01 sec
	 RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;
	 TIM15->CR1 &= 0xF470; // Configure timer 15
	 TIM15->ARR = 63999; // Set reload value
	 TIM15->PSC = 0x09; // Set prescale value

	 TIM15->CR1 |= 0x0001; //counter enable

	 TIM15->DIER |= 0x0001; // Enable timer 15 interrupts
	 NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0); // Set interrupt priority
	 NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt
}

void TIM1_BRK_TIM15_IRQHandler(void) {
	runtime++;
	TIM15->SR &= ~0x0001; // Clear interrupt bit
 }

// TIMER ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
