/**
 * @file        main.h
 * @author      Leonardo Acha Boiano
 * @date        20 Feb 2023
 * @brief       Embedded systems II: LAB 01
 *
 * @note        This code is written in C and is used on a Blue Pill development board.
 *
 * @copyright   Copyright (c) 2023 by Leonardo Acha Boiano. All rights reserved.
 *
 */

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"

// Task functions prototype
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

// Task parameter to be sent to the task function
const char *pvTask1  = "Task1 is running";
const char *pvTask2  = "Task2 is running";

#endif

	
/********************************* END OF FILE ********************************/
/******************************************************************************/
