/**
******************************************************************************
* @file		main.c
* @brief    	Main program file for STM32F103C6 development board.
*           	Initializes system resources and starts the FreeRTOS scheduler.
* @author	Leonardo Acha Boiano
* @date		26 March 2023
******************************************************************************
*/

#include "main.h"

SemaphoreHandle_t xMutex; /*!< Semaphore used to protect access to shared resources. */
QueueHandle_t queue1; /*!< Queue used for communication between tasks. */
QueueHandle_t queue2; /*!< Queue used for communication between tasks. */
BaseType_t result;

/**
 * @brief  The main function of the program.
 *
 * @return None.
 */
int main(){
    /* Initialize system resources */
    setup_RCC();
    setup_GPIO(); 

    /* Initialize tasks and queues */
    initialize_tasks();

    /* Start FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    while(1) {
    }
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
