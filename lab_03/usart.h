/**
  ******************************************************************************
  * @file		usart.h
  * @author	Leonardo Acha Boiano
  * @date		09 July 2022
  * @note		Re-write from Book
  ******************************************************************************
  */
	
#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "semphr.h"

//Declare global variables
extern SemaphoreHandle_t xMutex;

void usart1_init(void);
void usart1_sendByte(unsigned char c);
void usart1_sendInt(uint8_t i);
void usart1_sendStr(char *str);

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/