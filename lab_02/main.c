#include "FreeRTOS.h"
#include "task.h"
// TODO: Include Semaphores Exercise 2

#include "gpio.h"

// Simple random delay
void vSimpleDelay(uint32_t  t);

// TODO: Global Variables here
//ola como tas 

// END TODO

// Task functions
void vTask1(void* pvParameters);
void vTask2(void* pvParameters);

int main(){

	setup_RCC();
	setup_GPIO();

	BaseType_t result = pdPASS;
	
	result = xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	configASSERT(result == pdPASS)
	
	// result = xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	configASSERT(result == pdPASS)
	
	vTaskStartScheduler();
	
	
	while(1) {
	}
}



void vSimpleDelay(uint32_t  t)
{
	t*=10000; //Multiply by 10000 to get delay in ms
	for (uint32_t i=0; i<t; i++) __NOP();
}

/*
*	@Brief Embedded Systems II (ES II) Lab 2
* 
* The goal of this lab is that the students get to know the OS
* FreeRTOS and concepts related to shared resources.
* 
* This functions implements the task 1 and task 2
* where task1 could be a blue LED and task2 could be a green LED
* 
* TODO:
*     Change to your Ports and pins
*     Exercise 1: Shared resources
*     Exercise 2: Semph
*/
void vTask1(void* pvParameters){

		// Critical section starts from here!
		GPIOB->ODR |= GREEN;
		Access(RED); //set RED
		vSimpleDelay(1000);
		Release(RED); //borrar valor del registro
		GPIOB->ODR &= ~GREEN;
		// Critical section ends here!
			
		vTaskDelete(NULL);
}

void vTask2(void* pvParameters){

		// Critical section starts from here!
		GPIOA->ODR |= BLUE;
		Access(RED);
		vSimpleDelay(1000);
		Release(RED);
		GPIOA->ODR &= ~BLUE;
		// Critical section ends here!
			
		vTaskDelete(NULL);
}

