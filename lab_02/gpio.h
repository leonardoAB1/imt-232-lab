#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>														
#include <stdlib.h>

#include "stm32f10x.h"
//#include "stm32f10xx_hal_gpio.h"

#define RMIN 			configCPU_CLOCK_HZ/10				// Use timer value to set a min interval
#define RMAX 			configCPU_CLOCK_HZ					// Use timer value to set a max interval
#define RDIV 			10													// Divider
#define RAMT 			(RMAX - RMIN)/RDIV					// Use interval to geta multiplier


// TODO: Change this registers to yours
#define GREEN    	GPIO_ODR_OD5								// Initial number of waiting cycles
#define RED      	GPIO_ODR_OD6								// Initial number of waiting cycles
#define BLUE     	GPIO_ODR_OD7								// Initial number of waiting cycles


/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions simulates a shared resource. In this case, a RED LED
* The task takes the resource
*/
void Access(unsigned int color);


/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions simulates a shared resource. In this case, a RED LED
* The task releases the resource
*/
void Release(unsigned int color);


/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions simulates a shared resource. In this case, a RED LED
* TODO:
*     Verify whether the resource is taken or not
*/
int Check(unsigned short color);


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
void setup_RCC(void);
void setup_GPIO(void);


#endif /* GPIO_H_ */
