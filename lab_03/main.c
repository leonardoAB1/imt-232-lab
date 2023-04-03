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

TaskHandle_t squareTask;
TaskHandle_t decrementTask;
TaskParams_t taskParams;
SemaphoreHandle_t xMutex; /*!< Semaphore used to protect access to shared resources. */
SemaphoreHandle_t usartMutex; /*!< Semaphore used to protect access to usart. */
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
	usart1_init();
	usart1_sendStr("\n\rSistema Inicializado");
    
    /* Start FreeRTOS scheduler */
    usart1_sendStr("\n\rInicializando Cronograma");
    vTaskStartScheduler();

    /* Should never reach here */
    while(1) {
    }
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
