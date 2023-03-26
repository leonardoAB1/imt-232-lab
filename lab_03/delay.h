/**
  ******************************************************************************
  * @file		delay.h
  * @author	Leonardo Acha Boiano
  * @date		09 July 2022
  * @note		Re-write from Book
  ******************************************************************************
  */
	
#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"
/*
@Input - ms: Delay�s time in ms.
@Output - void
@Description - se crea un delay falso mediante el uso de un for loop vacio.
*/
void delay_ms(uint32_t  t);

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/