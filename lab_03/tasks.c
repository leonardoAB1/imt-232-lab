/**
******************************************************************************
* @file		task.c
* @brief		This file contains the implementation of the tasks created
* 				in FreeRTOS for the stm32f103c6. The tasks implemented are
*				"SquareTask" and "DecrementTask".
* @date		26 March 2023
******************************************************************************
*/

#include "tasks.h"

/**
 * @brief Initializes the tasks and creates the task table.
 * 
 */
void initialize_tasks(void)
{

	// Handle creation
	xMutex = xSemaphoreCreateMutex();
	usartMutex = xSemaphoreCreateMutex();
	// xQueueCreate(items in queue,  item's size in bytes)
	queue1 = xQueueCreate(QUEUE_ITEM_NUMBER, sizeof(uint32_t));
	queue2 = xQueueCreate(QUEUE_ITEM_NUMBER, sizeof(uint32_t));

	taskParams.param1 = queue1;
	taskParams.param2 = queue2;

	TaskInitParams_t const TaskInitParameters[] = {
		// Pointer to the Task function, Task String Name, The task stack depth, Parameter Pointer, Task priority, Task Handle
		{(TaskFunction_t)SquareTask, "SquareTask", TASK_SQUARE_STACK_DEPTH, &taskParams, TASK_SQUARE_PRIORITY, squareTask},
		{(TaskFunction_t)DecrementTask, "DecrementTask", TASK_DECREMENT_STACK_DEPTH, &taskParams, TASK_DECREMENT_PRIORITY, decrementTask}};

	// Loop through the task table and create each task.
	for (uint8_t TaskCount = 0;
		 TaskCount < sizeof(TaskInitParameters) / sizeof(TaskInitParameters[0]);
		 TaskCount++)
	{
		result = xTaskCreate(TaskInitParameters[TaskCount].TaskCodePtr,
							 TaskInitParameters[TaskCount].TaskName,
							 TaskInitParameters[TaskCount].StackDepth,
							 TaskInitParameters[TaskCount].ParametersPtr,
							 TaskInitParameters[TaskCount].TaskPriority,
							 TaskInitParameters[TaskCount].TaskHandle);
		configASSERT(result == pdPASS) // Make sure the task was created successfully
	}
	
}

/**
 * @brief The task that calculates the square of a number.
 * 
 * This task calculates the square of a number and communicates the result to the "DecrementTask" 
 * task using a queue. The task receives a value from "DecrementTask" using another queue.
 * 
 * @param pvParameters Pointer to the task parameters.
 */
void SquareTask(void *pvParameters)
{
	//Handles
	TaskParams_t* params = (TaskParams_t*) pvParameters;
	QueueHandle_t queue1 = params->param1;
	QueueHandle_t queue2 = params->param2;

	//String to print values by usart
	char str[30];

	//variables a enviar
	uint32_t y = 4;

	usart1_sendStr("\n\rVariables de SquareTask Inicializadas");
	sprintf(str,"\n\ry=%d", y);
	usart1_sendStr(str);
	while (1)
	{		
		sprintf(str,"\n\ry=%d", y);
		usart1_sendStr(str);
		// Take
		if (xQueuePeek(queue2, &y, 0) == pdTRUE) 
		{
			xQueueReceive(queue2, &y, portMAX_DELAY);
		}
		// Do something
		y = y * y; //Square value
		if (y>=10000)
		{
			y=4;
		}
		// Give
		xQueueSendToBack(queue1, &y, portMAX_DELAY);
		
		xSemaphoreTake(xMutex, portMAX_DELAY);
		// Critical section starts from here!
		Access(BLUE); // Set BLUE LED
		Access(RED); // Set RED LED
		delay_ms(1000); // Wait for 1 second
		Release(RED); // Clear the value of RED LED
		Release(BLUE); // Clear the value of BLUE LED
		// Critical section ends here!
		// vTaskDelay(pdMS_TO_TICKS(1000));
		xSemaphoreGive(xMutex);
	}
}
/**
 * @brief The task decrements by one the value of a number.
 * 
 * La rutina de DecrementTask debera:
	1. Esperar por el valor al ser recibido
	2. Disminuir el valor recibido en uno y actualizar su variable local con el resultado de esta operaci ́on
	3. Comunicar el valor de su variable local a la tarea SquareTask usando una fila
	4. Repetir desde (1)
 * 
 * @param pvParameters Pointer to the task parameters.
 */
void DecrementTask(void *pvParameters)
{
	TaskParams_t* params = (TaskParams_t*) pvParameters;
	QueueHandle_t queue1 = params->param1;
	QueueHandle_t queue2 = params->param2;
	//String to print values by usart
	char str[30];

	//variable to send
	uint32_t y=0;

	usart1_sendStr("\n\rVariables de DecrementTask Inicializadas");
	sprintf(str,"\n\ry=%d", y);
	usart1_sendStr(str);
	while (1)
	{	
		sprintf(str,"\n\ry=%d", y);
		usart1_sendStr(str);
		
		// Take
		if (xQueuePeek(queue1, &y, 0) == pdTRUE) 
		{
			xQueueReceive(queue1, &y, portMAX_DELAY);
		}
		// Do something
		y = y - 1;
		// Timeout occurred, handle the error
		//usart1_sendStr("\n\rTimeout ocurred");
		// Give
		xQueueSendToBack(queue2, &y, portMAX_DELAY);
		
		xSemaphoreTake(xMutex, portMAX_DELAY);
		// Critical section starts from here!
		Access(GREEN);
		Access(RED); // Set RED LED

		delay_ms(1000); // Wait for 1 second
		Release(RED); // Clear the value of RED LED
		Release(GREEN); // Clear the value of GREEN LED
		// vTaskDelay(pdMS_TO_TICKS(1000));
		// Critical section ends here!
		xSemaphoreGive(xMutex);
	}
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
