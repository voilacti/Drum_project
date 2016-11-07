#ifndef PWM_H
#define PWM_H

#include "stm32f10x.h"

/** 
Example :
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    Port_IO_Init_Alter_PP(GPIOA,1);
    PWM_Init(TIM2, 2, 1);
    PWM_Start(TIM2, 2, 0.3);
**/


/* @param TIM2 (CH)2 freq_pwm_souhaite
* @return resolution(arr)
*/
/*
Alternate function remapping IO et Arduino :
	TIM1_CH1	PA8		D7
	TIM1_CH2	PA9		D8
	TIM1_CH3	PA10	D2
	TIM2_CH1	PA0		A0
	TIM2_CH2	PA1		A1 
	TIM3_CH1	PA6		D12
	TIM3_CH2	PA9		D11
*/
vu16 PWM_Init(TIM_TypeDef *timer, char channel, u32 duree_us);

/**
*configurer CCR correspondant avec un rapport cyclique entre 0 et 1
*il faut d'abord init ce pwm
**/
void PWM_Start(TIM_TypeDef *timer, char channel, float rapport_cyclique);

#endif 
