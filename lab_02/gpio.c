
#include "gpio.h"					// Lab specific defines/declarations

#include <stdint.h>				// Standard Integer - data type definitions

/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions simulates a shared resource. In this case, a RED LED
* The task takes the resource
* TODO: Change the port if necessary
*/
void Access(unsigned int color) {
	// set green led to 1
	switch (color)
	{
	case BLUE:
		GPIOC->ODR &= ~color;
		break;
	case GREEN:
		GPIOB->ODR |= color;
		break;
	case RED:
		GPIOA->ODR |= color;
		break;
	default:
		break;
	}
}


/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions simulates a shared resource. In this case, a RED LED
* The task releases the resource
* TODO: Change the port if necessary
*/
void Release(unsigned int color) {
	// set red led to 0
	switch (color)
	{
	case BLUE:
		GPIOC->ODR |= color;
		break;
	case GREEN:
		GPIOB->ODR &= ~color;
		break;
	case RED:
		GPIOA->ODR &= ~color;
		break;
	default:
		break;
	}
}



/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions simulates a shared resource. In this case, a RED LED
* TODO:
*     Verify whether the resource si taken or not
*/
int Check(unsigned short color) {
	switch (color)
	{
	case BLUE:
		if (GPIOC->ODR & GPIO_ODR_ODR13){
			return 1;
		}
		break;
	case GREEN:
		if (GPIOB->ODR & GPIO_ODR_ODR1){
			return 1;
		}
		break;
	case RED:
		if (GPIOA->ODR & GPIO_ODR_ODR12){
			return 1;
		}
		break;
	default:
		break;
	}
	return 0;
}


/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions setups the gpios. In this case, a GREEN LED and BlUE LED
* TODO:
*     Change this function corresponding to your platform
*/
void setup_RCC(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN|RCC_APB2ENR_IOPCEN; //enable GPIO clock
}

/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions setups the gpios. In this case, a GREEN LED and BlUE LED
* TODO:
*     Change this functions corresponding to your platform
*/
void setup_GPIO(void){
	// PA12 PB1 PC13 as outputs
	GPIOA->CRH |= 0x00030000;	
	GPIOB->CRL |= 0x00000030;
	GPIOC->CRH |= 0x00300000;
  	// make ports A, B, C low
  	GPIOA->ODR &= ~0xFFFFFFFF; //RED
	GPIOB->ODR &= ~0xFFFFFFFF; //GREEN
	GPIOC->ODR |= GPIO_ODR_ODR13; //BLUE
}

