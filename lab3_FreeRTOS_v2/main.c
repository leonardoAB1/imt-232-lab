#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "gpio.h"

// Simple random delay
void vSimpleDelay(void);

//estructura creada para guardar las Queues
typedef struct{

	QueueHandle_t xQueueSqrt;
	QueueHandle_t xQueueDecr;
	
} TaskQueues_t;

// Task functions
void vSquareTask(void* pvParameters);
void vDecrementTask(void* pvParameters);


#define LARGE	5
#define ITEM_SIZE	sizeof(uint32_t)

TaskQueues_t taskQueues;

int main(){
	//Configuracion del RCC y el GPIO
	setup_RCC();
	setup_GPIO();
	
	//Creacion de los manejadores de las Queues
	QueueHandle_t xQueueSqrt = NULL;
	QueueHandle_t xQueueDecr = NULL;
	
	//Creacion de las Queues
	xQueueSqrt = xQueueCreate(LARGE, ITEM_SIZE);
	xQueueDecr = xQueueCreate(LARGE, ITEM_SIZE);
	

	//Se guardan las Queues en la estructura creada previamente
	taskQueues.xQueueSqrt = xQueueSqrt;
	taskQueues.xQueueDecr = xQueueDecr;
	
	//Se convierte la estructura en un puntero vacio	
	void* pvPointer = (void*)&taskQueues;

	BaseType_t result = pdPASS;
	
	//Se crean las 2 tasks que se usaran
	result = xTaskCreate(vSquareTask, "SquareTask", configMINIMAL_STACK_SIZE, pvPointer, 1, NULL);
	configASSERT(result == pdPASS)
	result = xTaskCreate(vDecrementTask, "DecrementTask", configMINIMAL_STACK_SIZE, pvPointer, 1, NULL);
	configASSERT(result == pdPASS)
	
	//inicio del cronograma
	vTaskStartScheduler();
	
	
	return 0;
}



void vSimpleDelay(void) {
	uint32_t nCount = 8000000;
	for(uint32_t i=0; i < nCount; i++) {
		__NOP();
	}
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
void vSquareTask(void* pvParameters){
		//variables a enviar
		uint32_t square = 4;
		uint32_t decrement_recieved = 0;
		//variables para acceder a los QueueHandle
		TaskQueues_t* pcPointer;
		QueueHandle_t xQueueSqrt;
		QueueHandle_t xQueueDecr;
	
		while(1){
		//Acceso a ambos QueueHandle
		pcPointer = (TaskQueues_t*)pvParameters;
		xQueueSqrt = pcPointer->xQueueSqrt;
		xQueueDecr = pcPointer->xQueueDecr;
			
		//Envio de Square	
		xQueueSendToBack(xQueueSqrt, &square, portMAX_DELAY);	
			
		//Espera para recibir Decrement
		xQueueReceive(xQueueDecr, &decrement_recieved, portMAX_DELAY);
			
		//Led indicador
		GPIOA->ODR |= GREEN;
		vTaskDelay(pdMS_TO_TICKS(1000));
			
		//Eleva al cuadrado el valor recibido si es menos de 10000
		if(square < 10000){
			square = decrement_recieved*decrement_recieved;
		}else{			//Si es mayor a 10000, este enciende el led rojo indicador y procede a eliminarse
			Access(RED);
			GPIOA->ODR &= ~GREEN;
			vTaskDelay(pdMS_TO_TICKS(1000));
			Release(RED);
			vTaskDelay(pdMS_TO_TICKS(1000));
			vTaskDelete(NULL);
		
		}
		//Apaga el led indicador
		GPIOA->ODR &= ~GREEN;
		vTaskDelay(pdMS_TO_TICKS(1000));
		
		}
		// Critical section ends here!
		
}


void vDecrementTask(void* pvParameters){
		//variables a enviar
		uint32_t decrement = 0;
		uint32_t square_recieved = 0;
		//variables para acceder a los QueueHandle	
		TaskQueues_t* pcPointer;
		QueueHandle_t xQueueSqrt;
		QueueHandle_t xQueueDecr;
	
		while(1){
		//Acceso a ambos QueueHandle
		pcPointer = (TaskQueues_t*)pvParameters;
		xQueueSqrt = pcPointer->xQueueSqrt;
		xQueueDecr = pcPointer->xQueueDecr;
			
		//Espera para recibir Square
		xQueueReceive(xQueueSqrt, &square_recieved, portMAX_DELAY);
			
		//Enciende el led indicador
		GPIOA->ODR |= BLUE;	
		vTaskDelay(pdMS_TO_TICKS(1000));
			
		//Resta el valor recibido en -1 si es menor a 10000
		if(decrement < 10000){
			decrement = square_recieved-1;
		}else{			//Si es mayor a 10000, enciende el led rojo y se elimina
			Access(RED);
			GPIOA->ODR &= ~BLUE;
			vTaskDelay(pdMS_TO_TICKS(1000));
			Release(RED);
			vTaskDelay(pdMS_TO_TICKS(1000));
			vTaskDelete(NULL);
		}
		
		//Envia el valor que se habia restado
		xQueueSendToBack(xQueueDecr, &decrement, portMAX_DELAY);		
		
		//apaga el led indicador
		GPIOA->ODR &= ~BLUE;
		vTaskDelay(pdMS_TO_TICKS(1000));
		
		}
}

