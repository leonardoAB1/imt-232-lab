
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
  	if (color==BLUE){
		GPIOC->ODR &= ~color;
		}	
	else if (color==GREEN){
		GPIOB->ODR |= color;
		}	
	else if (color==RED){
		GPIOA->ODR |= color;
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
	if (color==BLUE){
		GPIOC->ODR |= color;
		}	
	else if (color==GREEN){
		GPIOB->ODR &= ~color;
		}	
	else if (color==RED){
		GPIOA->ODR &= ~color;
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
	return color;
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
  	// make PA12 low, PB1 low, PC13 low
  	GPIOA->ODR &= ~GPIO_ODR_ODR12;
	GPIOB->ODR &= ~GPIO_ODR_ODR1;
	GPIOC->ODR |= GPIO_ODR_ODR13;
}

