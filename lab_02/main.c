#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "gpio.h"

// Simple random delay
void vSimpleDelay(uint32_t  t);

// TODO: Global Variables here
uint8_t token = 0;

// END TODO

// Task functions
void vTask1(void* pvParameters);
void vTask2(void* pvParameters);

int main(){
	//__disable_irq();
	setup_RCC();
	setup_GPIO();
	//__enable_irq();

	BaseType_t result = pdPASS;
	
	result = xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	configASSERT(result == pdPASS)
	
	result = xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
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
	while (token!=0){
		__NOP();
	}
	vSimpleDelay(2000);
	// Critical section starts from here!
	Access(BLUE);
	Access(RED); //set RED
	vSimpleDelay(1000);
	Release(RED); //borrar valor del registro
	Release(BLUE);
	// Critical section ends here!
	token=1-token;
	vTaskDelete(NULL);
}

void vTask2(void* pvParameters){
	while (token!=1){
		__NOP();
	}
	vSimpleDelay(2000);
	// Critical section starts from here!
	Access(GREEN);
	Access(RED);
	vSimpleDelay(1000);
	Release(RED);
	Release(GREEN);
	// Critical section ends here!
	token=1-token;
	vTaskDelete(NULL);
}

/*RESPUESTAS
1.2. 	El task1 se realiza sin problema.
1.3. 	Al descomentar el task2 se crea la segunda task, 
		en teoria se deberian prender y apagar el led verde, 
		azul y rojo. Tras cargar el codigo observamos que el
		LED azul se queda prendido.
1.4. 	MUTEX: CHECK
		Se desarrolla la task2 y a continuación la task1. Por tanto, 
		da la impresion de que esto impone mutex(mutual exclusion).
1.5. 	En efecto, hay un momento en el que los tres LEDs
		se encuentran prendidos. Esto implica que el cronograma
		hace el cambio entre tasks para que se ejecuten de
		manera concurrente DURANTE la seccion critica.
1.6.	MUTEX: TOKEN
		A primera vista el uso del token 
		pareciera imponer mutex.

		Tras crear el semaforo se observa la siguiente secuencia:
		VERDE Y ROJO
		AZUL Y ROJO
		Es decir, las 2 task se ejecutan secuancialmente.

*/
