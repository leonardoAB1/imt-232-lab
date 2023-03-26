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

// Define the stack depth and priority for the SquareTask
#define TASK_SQUARE_STACK_DEPTH configMINIMAL_STACK_SIZE
#define TASK_SQUARE_PRIORITY 1

// Define the stack depth and priority for the DecrementTask
#define TASK_DECREMENT_STACK_DEPTH configMINIMAL_STACK_SIZE
#define TASK_DECREMENT_PRIORITY 1

// Declare global variables
extern SemaphoreHandle_t xMutex;
extern QueueHandle_t queue1;
extern QueueHandle_t queue2;
extern BaseType_t result;

// Declare function prototypes
void initialize_tasks(void);
void SquareTask(void* pvParameters) __attribute__((noreturn));
void DecrementTask(void* pvParameters) __attribute__((noreturn));

#endif /* _TASKS_H_ */

/********************************* END OF FILE ********************************/
/******************************************************************************/
