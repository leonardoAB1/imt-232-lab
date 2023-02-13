/**
 * @file        main.h
 * @author      Leonardo Acha Boiano
 * @date        09 Feb 2023
 * @brief       Embedded systems II: LAB 00
 *
 * This program sets the outputs of a Blue Pill development board based on inputs
 * received from buttons connected to the board. The program sets three digital
 * inputs, PA4, PA5, and PA6, with pull-up resistors and four outputs, PB13,
 * PB14, PB15, and PA8(PWM). The inputs control the duty cycle of a PWM signal on PA8
 * and the color of an RGB LED connected to the board.
 *
 * PA4: button_1: Set color red, duty cycle 0%
 * PA5: button_2: Set color green, duty cycle 50%
 * PA6: button_3: Set color blue, duty cycle 100%
 *
 * @note        This code is written in C and is used on a Blue Pill development board.
 *
 * @copyright   Copyright (c) 2023 by Leonardo Acha Boiano. All rights reserved.
 *
 */

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"

void EXTI4_IRQHandler(void);
void EXTI5_IRQHandler(void);
void EXTI6_IRQHandler(void);

#endif

	
/********************************* END OF FILE ********************************/
/******************************************************************************/
