/**
  ******************************************************************************
  * @file		usart.c
  * @author	Leonardo Acha Boiano
  * @date		09 July 2022
  * @note		Re-write from Book
  ******************************************************************************
  */

#include "usart.h"

void usart1_init()
{
    RCC->APB2ENR |= (1<<14);					//enable USART1 clock
	RCC->APB1ENR |= (1<<0);						//enable TIM2 clock
	GPIOA	->	ODR |=(1<<10); 					// pull-up PA10
	GPIOA	->	CRH = 0x444448B4; 			    // (PA10)RX1=input with pull-up, (PA9)TX1=alt. func output
	USART1	->	CR1 = 0x200C;					// Configure Control Register Value for 1 stop, 8 data, no parity and  enable transmitter and receiver
	USART1	->	BRR = 7500;						// 72MHz/9600bps=7500=clock divisor
}

void usart1_sendByte(unsigned char c)
{
	while((USART1->SR&(1<<6)) == 0);	//wait until the TC flag is set
	USART1->DR=c;
}

/*the function sends a zero-ending string through USART1*/
void usart1_sendStr(char *str)
{
	while(*str != 0)
	{
		usart1_sendByte(*str);
		str++;
	}
}

/* The function sends a number through USART1*/
void usart1_sendInt(uint8_t i)
{
	char str[10];
	sprintf(str,"%d",i);

	usart1_sendStr(str);
}

/********************************* END OF FILE ********************************/
/******************************************************************************/