/*******************************************************************************
 * @file        main.c
 * @author      Leonardo Acha Boiano
 * @date        20 Feb 2023
 * @brief       Embedded systems II: LAB 01
 *
 * Este laboratorio introduce el concepto de tasks en un sistema operativo de tiempo real (RTOS). Para este
 * proposito, se uso FreeRTOS, que esta dise ̃nado para ejecutar aplicaciones con requisitos de tiempo real suaves
 * en sistemas embebidos. Permite que una aplicacion se divida en tareas independientes, lo cual es importante
 * cuando se trata de diferentes requisitos en tiempo real. Conceptualmente, FreeRTOS es un kernel en tiempo
 * real que se ocupa del manejo de tareas y permite que las aplicaciones integradas usen multitarea. A diferencia
 * de las plataformas multiprocesador, los sistemas embebidos a menudo contienen solo un procesador que puede
 * ejecutar solo una tarea a la vez. En FreeRTOS, esta tarea se define en estado Running, como se ilustra en la
 * Imagen 1. Todas las dem ́as tareas estan en estado No running. El kernel decide cundo y que tarea debe pasar
 * al estado Running y, en consecuencia, determina un cronograma para la aplicacion.
 * Se realizara una aplicacion basica con m ́ultiples tareas y se presentara los conceptos de tasks y cronogramas. Se
 * recomienda usar la documentacion. El libro ‘Mastering the FreeRTOS Real Time Kernel‘ y el reference manual
 * del sistema operativo utilizado ‘FreeRTOS Reference Manual‘ para entender mejor cada una de las funciones
 * que se esta usando.
 * 
 * @note        This code is written in C and is used on a Blue Pill development board.
 *
 * @copyright   Copyright (c) 2023 by Leonardo Acha Boiano. All rights reserved.
 *
 *******************************************************************************/

#include "main.h"

int main()
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN; //enable GPIO clock
  	// PA12 PB1 PB5 as outputs
	GPIOA->CRH |= 0x00030000;	
	GPIOB->CRL |= 0x00300030;
  	// make PA12 high, PB1 low, low PB5
  	GPIOA->BSRR|= (1 << 12);
	GPIOB->BSRR|= (1 << 1)|(1 << 21);
	
    TaskHandle_t task1_Handle = NULL;
    xTaskCreate(vTask1,         // Pointer to the function
	"Task 1",                   // Text name for the task
    1000,                       // Stack depth in words
	(void*)pvTask1,	            // Parameter passed into the task
	configMAX_PRIORITIES-1,		// Priority of the task
	&task1_Handle );		    // Handle to the task

    TaskHandle_t task2_Handle = NULL;
    xTaskCreate(vTask2,         // Pointer to the function
	"Task 2",                   // Text name for the task
    1000,                       // Stack depth in words configMINIMAL_STACK_SIZE
	(void*)pvTask2,	            // Parameter passed into the task
	1,			                // Priority of the task
	&task2_Handle );		    // Handle to the task
	
    // Start the scheduler so our tasks start executing
	vTaskStartScheduler();
    /* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	while(1){
	}
}

/*-----------------------------------------------------------*/
void vTask1( void *pvParameters )
{
char *pcTaskName = (char *) pvParameters;
	// Task is implemented in an infinite loop. 
	while(1)
	{
		//GPIOB->ODR ^= (GPIO_ODR_ODR1);
		GPIOB->ODR ^= (GPIO_ODR_ODR5);
		// GPIOA->ODR ^= (GPIO_ODR_ODR12);
		// Delay for a period. 
		vTaskDelay( 1000 / portTICK_PERIOD_MS );
	}
}
/*-----------------------------------------------------------*/
void vTask2( void *pvParameters )
{
char *pcTaskName = (char *) pvParameters;
	// Task is implemented in an infinite loop. 
	while(1)
	{
		// GPIOB->ODR ^= (GPIO_ODR_ODR1);
		// GPIOB->ODR ^= (GPIO_ODR_ODR5);
	  GPIOA->ODR ^= (GPIO_ODR_ODR12);
		// Delay for a period. 
		vTaskDelay( 750 / portTICK_PERIOD_MS );
	}
} 
/********************************* END OF FILE ********************************/
/******************************************************************************/
