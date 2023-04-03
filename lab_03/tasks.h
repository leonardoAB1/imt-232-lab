/**
******************************************************************************
* @file		task.h
* @brief	Header file for tasks.c, which contains task definitions and
* 			initialization function
* @date		26 March 2023
******************************************************************************
*/

#ifndef _TASKS_H_
#define _TASKS_H_

#include "FreeRTOS.h"
#include "gpio.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "delay.h"
#include "usart.h"

// Define the stack depth and priority for the SquareTask
#define TASK_SQUARE_STACK_DEPTH configMINIMAL_STACK_SIZE
#define TASK_SQUARE_PRIORITY 2

// Define the stack depth and priority for the DecrementTask
#define TASK_DECREMENT_STACK_DEPTH configMINIMAL_STACK_SIZE
#define TASK_DECREMENT_PRIORITY 1
#define QUEUE_ITEM_NUMBER 5

//Declare task params structure
typedef struct
{
	QueueHandle_t param1;
	QueueHandle_t param2;

} TaskParams_t;

/*
 * Task configuration structure used to create a task configuration table.
 * Note: this is for dynamic memory allocation. We create all the tasks up front
 * dynamically and then never allocate memory again after initialization.
 */
typedef struct
{
	TaskFunction_t const TaskCodePtr;		 /*< Pointer to the task function */
	const char *const TaskName;				 /*< String task name             */
	const configSTACK_DEPTH_TYPE StackDepth; /*< Stack depth                  */
	const void *ParametersPtr;				 /*< Parameter Pointer            */
	UBaseType_t TaskPriority;				 /*< Task Priority                */
	TaskHandle_t *const TaskHandle;			 /*< Pointer to task handle       */
} TaskInitParams_t;

// Declare global variables
extern TaskHandle_t squareTask;
extern TaskHandle_t decrementTask;
extern SemaphoreHandle_t xMutex;
extern SemaphoreHandle_t usartMutex;
extern QueueHandle_t queue1;
extern QueueHandle_t queue2;
extern BaseType_t result;
extern TaskParams_t taskParams;

// Declare function prototypes
void initialize_tasks(void);
void SquareTask(void* pvParameters) __attribute__((noreturn));
void DecrementTask(void* pvParameters) __attribute__((noreturn));

#endif /* _TASKS_H_ */

/********************************* END OF FILE ********************************/
/******************************************************************************/
