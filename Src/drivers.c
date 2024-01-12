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
<<<<<<< Updated upstream
=======



	 //BUZZER timer (TIM2)vvvvvvvvvvvvvvvv

	 RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
	 TIM2->CR1 &= 0xF400; // Configure timer 2
	 //TIM2->CR1 = 0x0000; // Configure timer 2
	 TIM2->ARR = 63999; // Set reload value //63999
	 TIM2->PSC = 0x0009; // Set prescale value

	 //TIM2->CR1 |= 0x0001; //counter enable

	  TIM2->CCER &= ~TIM_CCER_CC3P; // Clear CCER register
	  TIM2->CCER |= 0x00000001 << 8; // Enable OC3 output
	  TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
	  TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
	  TIM2->CCMR2 |= TIM_OCMode_PWM1; // Set output mode to PWM1
	  TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
	  TIM2->CCMR2 |= TIM_OCPreload_Enable;
	  TIM2->CCR3 = 63999 / 2; // Set duty cycle to 50 %

>>>>>>> Stashed changes
}

void TIM1_BRK_TIM15_IRQHandler(void) {
	runtime++;
	TIM15->SR &= ~0x0001; // Clear interrupt bit
 }

// TIMER ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


//I2C shit TODO: ret kommentar
void I2C_Write(uint16_t address, uint8_t reg, uint8_t val) {
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_Reload_Mode, I2C_Generate_Start_Write); // Initiate transfer

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, reg); // Send register address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TCR) == RESET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_AutoEnd_Mode, I2C_No_StartStop); // Resend address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, val); // Transfer data

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET); // Wait for stop flag

    I2C_ClearFlag(I2C1, I2C_FLAG_STOPF); // Clear stop flag
}


uint8_t I2C_Read(uint16_t address, uint8_t reg, uint8_t* vals, uint8_t n) {
    uint8_t val = 0;

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write); // Initiate transfer

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, reg); // Send register address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TC) == RESET); // Wait until free

    I2C_TransferHandling(I2C1, address, n, I2C_AutoEnd_Mode, I2C_Generate_Start_Read); // Resend address

    for (uint8_t i = 0 ; i < n ; i++) {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET); // Wait until free

        if (n > 1) { vals[i] = I2C_ReceiveData(I2C1); }
        else { val = I2C_ReceiveData(I2C1); } // Transfer data
    }

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET); // Wait for stop flag

    I2C_ClearFlag(I2C1, I2C_FLAG_STOPF); // Clear stop flag

    return val;
}

void I2C_init()
{

    /**************/
    /**** GPIO ****/
    /**************/
    RCC->AHBENR |= 0x00040000; // Enable clock for GPIO Bank B

    GPIOB->AFR[8 >> 0x03] &= ~(0x0000000F << ((8 & 0x00000007) * 4)); // Clear alternate function for PB8
    GPIOB->AFR[8 >> 0x03] |=  (0x00000004 << ((8 & 0x00000007) * 4)); // Set alternate 4 function for PB8
    GPIOB->AFR[9 >> 0x03] &= ~(0x0000000F << ((9 & 0x00000007) * 4)); // Clear alternate function for PB9
    GPIOB->AFR[9 >> 0x03] |=  (0x00000004 << ((9 & 0x00000007) * 4)); // Set alternate 4 function for PB9

    // Configure pins PB8 and PB9 for 10 MHz alternate function
    GPIOB->OSPEEDR &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear speed register
    GPIOB->OSPEEDR |=  (0x00000001 << (8 * 2) | 0x00000001 << (9 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER  &= ~(0x0001     << (8)     | 0x0001     << (9));        // Clear output type register
    GPIOB->OTYPER  |=  (0x0001     << (8)     | 0x0001     << (9));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER   &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear mode register
    GPIOB->MODER   |=  (0x00000002 << (8 * 2) | 0x00000002 << (9 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR   &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear push/pull register
    GPIOB->PUPDR   |=  (0x00000001 << (8 * 2) | 0x00000001 << (9 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    /*************/
    /**** I2C ****/
    /*************/
    RCC->APB1ENR |=  0x00200000; // Enable clock for I2C1

    I2C1->CR1 &= ~0x00000001;  // Disable I2C1 peripheral during config
    I2C1->CR1 &= 0x00CFE0FF;   // Clear config
    I2C1->CR1 |= 0x00000000;   // Set Analog filter (0x00000000 - Enabled, 0x00001000 - Disabled)
    I2C1->CR1 |= 0x00 << 8;    // Set digital filter (0x00 - 0x0F)
    I2C1->TIMINGR = 0x10805E89 & 0xF0FFFFFF; // Set timing register to 0x10805E89. See reference manual for more
    I2C1->CR1  |= 0x00000001;  // Enable I2C1 peripheral
    I2C1->OAR1  = 0x00000000;  // Clear own address register 1
    I2C1->OAR2  = 0x00000000;  // Clear own address register 2
    I2C1->OAR1 |= 0x00000000;  // Configure for 7-bit address (0x00000000 - 7-bit, 0x00000400 - 10-bit)
    I2C1->OAR1 |= 0xAB;        // Set own address to 0xAB
    I2C1->OAR1 |= 0x00008000;  // Enable own address acknowledgment
    I2C1->CR1  |= 0x00000000;  // Set mode (0x00000000 - I2C, 0x00200000 - SMBus Device, 0x00100000 - SMBus Host)
    I2C1->CR2  &= 0x07FF7FFF;  // Clear config 2
    I2C1->CR2  |= 0x00000000;  // Configure acknowledgment (0x00000000 - Enabled, 0x00008000 - Disabled)

	I2C_Write(0x98, 0x07, 0x01); //Turn on acc
	I2C_Write(0x98, 0x0A, 0x00); //Enable all tab axis
	I2C_Write(0x98, 0x09, 0x1F); //Set tabthreshold to max value 11111
}

//Potentiometers  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void analogConfigPorts(){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

	int pin = 0;
	GPIOA->MODER &= ~(0x00000003 << (2*pin));
	GPIOA->MODER |= 0x00000000 << (2*pin);
	GPIOA->PUPDR &= ~(0x00000003 << (2*pin));
	GPIOA->PUPDR |= 0x00000003 << (2*pin);

	RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12


	ADC1->CR = 0x00000000; // Clear CR register
	ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}

uint16_t readPotentiometer(){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	uint16_t potVal = ADC_GetConversionValue(ADC1);
	return potVal;
}

//LED vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void initRGB(){
	//setup PA9 (Blue)
		uint8_t pin = 9;
		GPIOA->OSPEEDR &= ~(0x00000003 << (2*pin));
		GPIOA->OSPEEDR |= (0x00000002 << (2*pin));
		GPIOA->OTYPER &= ~(0x0001 << (pin));
		GPIOA->OTYPER |= 0x0000 << (pin);
		GPIOA->MODER &= ~(0x00000003 << (2*pin));
		GPIOA->MODER |= 0x00000001 << (2*pin);

		//setup PC7 (Green)
		pin = 7;
		GPIOC->OSPEEDR &= ~(0x00000003 << (2*pin));
		GPIOC->OSPEEDR |= (0x00000002 << (2*pin));
		GPIOC->OTYPER &= ~(0x0001 << (pin));
		GPIOC->OTYPER |= 0x0000 << (pin);
		GPIOC->MODER &= ~(0x00000003 << (2*pin));
		GPIOC->MODER |= 0x00000001 << (2*pin);

		//setup PB4 (Red)
		pin = 4;
		GPIOB->OSPEEDR &= ~(0x00000003 << (2*pin));
		GPIOB->OSPEEDR |= (0x00000002 << (2*pin));
		GPIOB->OTYPER &= ~(0x0001 << (pin));
		GPIOB->OTYPER |= 0x0000 << (pin);
		GPIOB->MODER &= ~(0x00000003 << (2*pin));
		GPIOB->MODER |= 0x00000001 << (2*pin);
}

//Sets the color of the LED based on an array [R, G, B]
void RGBColor(uint8_t color[]){
	//Resets LED
	GPIOB->ODR |= (0x0001 << 4);
	GPIOC->ODR |= (0x0001 << 7);
	GPIOA->ODR |= (0x0001 << 9);

	if(color[0] == 1){ //Red PB4
		GPIOB->ODR &= (0x0000 << 4);
	}
	if(color[1] == 1){ //Green C7
		GPIOC->ODR &= (0x0000 << 7);
	}
	if(color[2] == 1){ //Blue A9
		GPIOA->ODR &= (0x000 << 9);
	}
}

//Flash memory
void writeToFlash(uint16_t data, uint32_t address){
	FLASH_Unlock();
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );
	FLASH_ErasePage(address);
	FLASH_ProgramHalfWord(address, data);
	FLASH_Lock();
}

uint16_t readFromFlash(uint32_t address){
	return *(uint16_t *)address;
}
