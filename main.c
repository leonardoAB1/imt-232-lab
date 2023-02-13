/*******************************************************************************
 * @file        main.c
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
 *******************************************************************************/

#include "main.h"

int main()
{
  // enable GPIO clocks and AFIO
  RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN);
  // enable TIM2 clock
  RCC->APB1ENR |= (1 << 0);
  // configure GPIOs
  // PA4 PA5 PA6 as inputs. Equivalent GPIOA->CRL = 0x08880000;
  GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6);
  GPIOA->CRL |= (GPIO_CRL_MODE4_0 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE6_0);
  // PA8 as alternate function output open-drain
  GPIOA->CRH = 0x000D;
  // PB13 PB14 PB15 as RGB outputs
  GPIOB->CRH = 0x11100000;
  // inputs as pull up
  GPIOA->ODR = (1 << 8);
  GPIOB->ODR = 0xE000; //(1<<13)|(1<<14)|(1<<15)

  // configure interrupts
  // enable AFIO
  // selecy interrupt input pin AFIO_EXTICR
  AFIO->EXTICR[0] = (AFIO->EXTICR[0] & 0xFFFFFFF0) | (0x1); // PA4
  AFIO->EXTICR[1] = (AFIO->EXTICR[1] & 0xFFFFFFF0) | (0x2); // PA5
  AFIO->EXTICR[2] = (AFIO->EXTICR[2] & 0xFFFFFFF0) | (0x3); // PA6

  // choose edge RTSR FTSR
  // Set the interrupt trigger to rising edge
  EXTI->RTSR |= EXTI_RTSR_TR4 | EXTI_RTSR_TR5 | EXTI_RTSR_TR6;

  // set EXTI_IMR to enable interrupts for the line
  // Enable the interrupt for PA4, PA5, and PA6
  EXTI->IMR |= EXTI_IMR_MR4 | EXTI_IMR_MR5 | EXTI_IMR_MR6;

  // enable EXTI interupt ISER on the NVIC_EnableIRQ function
  NVIC_EnableIRQ(EXTI4_IRQHandler);
  NVIC_EnableIRQ(EXTI5_IRQHandler);
  NVIC_EnableIRQ(EXTI6_IRQHandler);
  // clear PR flag in interrupt routine

  // configure pwm
  // duty cycle = (TIMx_CCRn*100)/(TIMx_ARR+1)
  // freq_gen_wave = (F_timer_clock/prescaler)/(ARR+1)
  // freq_gen_wave = (F_timer_clock)/((ARR+1)*(PSC+1))
  // TIMx_ARR_max = 719999
  // up counting CMS=0 DIR=0
  // OCnM=110 PWM1 mode
  // freq_gen_wave = 100
  // F_timer_clock = 72MHz
  // ARR = (F_timer_clock/prescaler)/(freq_gen_wave)-1
  // (ARR+1)*(PSC+1) = (F_timer_clock/freq_gen_wave)
  // (ARR+1)*(PSC+1) = (72MHz/100)
  // If PSC=719 -> ARR=999
  TIM2->CCER = 0x1 << 0; // CC1P=0, CC1E=1
  TIM2->CCMR1 = 0x0068;  // OC1M=PWM1, OC1PE=1
  TIM2->CR1 = 0x80;      // Auto reload preload enable

  TIM2->PSC = 719; // presscaler=719
  TIM2->ARR = 999;
  TIM2->CCR1 = 0; // duty cycle = (TIM2_CCR1*100)/(999+1)

  TIM2->EGR = 1;     // UG=1
  TIM2->CR1 |= 0x01; // timer enable (CEN=1)
}

void EXTI4_IRQHandler(void)
{
  // Interrupt handler for PA4
  if (EXTI->PR & EXTI_PR_PR4)
  {
    // Clear the interrupt pending bit
    EXTI->PR |= EXTI_PR_PR4;

    // Interrupt code here
    // set red
    // make PB13 high, PB14 low, PB15 low
    GPIOB->BSRR = (1 << 13) | (1 << 30) | (1 << 31);
    TIM2->CCR1 = 0; // duty cycle 0%
  }
}

void EXTI5_IRQHandler(void)
{
  // Interrupt handler for PA5
  if (EXTI->PR & EXTI_PR_PR5)
  {
    // Clear the interrupt pending bit
    EXTI->PR |= EXTI_PR_PR5;

    // Interrupt code here
    // set green
    // make PB13 low, PB14 high, PB15 low
    GPIOB->BSRR = (1 << 29) | (1 << 14) | (1 << 31);
    TIM2->CCR1 = 500; // duty cycle 50%
  }
}

void EXTI6_IRQHandler(void)
{
  // Interrupt handler for PA6
  if (EXTI->PR & EXTI_PR_PR6)
  {
    // Clear the interrupt pending bit
    EXTI->PR |= EXTI_PR_PR6;

    // Interrupt code here
    // set blue
    // make PB13 low, PB14 low, PB15 high
    GPIOB->BSRR = (1 << 29) | (1 << 30) | (1 << 15);
    TIM2->CCR1 = 1000; // duty cycle 100%
  }
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
