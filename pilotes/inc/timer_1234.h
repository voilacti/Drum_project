/**
  ******************************************************************************
  * @file    gpio.h
  * @author  Quentin Leclerc & Nathan Balblanc
  * @date    16-September-2016
**/

#ifndef TIMER_1234_H
#define TIMER_1234_H

#include "stm32f10x.h"
#include "clock.h" 
#include "gpio.h"

u32 Timer_1234_Init(TIM_TypeDef *Timer, u32 Frequence ) ;
void Timer_Active_IT(TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void)); 

void (* ptr_fonc) (void) ;

#endif 