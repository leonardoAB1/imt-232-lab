
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
  GPIOA->ODR |= color;
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
	GPIOA->ODR &= ~color;	
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

uint32_t mivariable = 0;

int Check(unsigned short color) {
	return GPIOA->ODR & color;
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
	RCC->AHBENR |= (1U<<17);
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
	GPIOA->MODER |= GPIO_MODER_MODER0_0;
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
}

