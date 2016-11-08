#ifndef PWM_H
#define PWM_H

#include "stm32f10x.h"
#include "clock.h"
#include "timer_1234.h"

/** 
* Configure l'PWM example
*   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    Port_IO_Init_Alter_PP(GPIOA,1);
    PWM_Init(TIM2,2,1);
    PWM_set_Cycle(TIM2,2,0.3);
**/


/* @param TIM2 (CH)2 freq_pwm_souhaite
* @return resolution(arr)
*/
/* Mapping des IO et Arduino: (Configurer en Alter PP)
* TIM1_CH1 PA8 D7 * CH2 PA9 D8 *CH3 PA10 D2
* TIM2_CH1 PA0 A0 * CH2 PA1 A1 
* TIM3_CH1 PA6 D12 / PB4 D5 * CH2 PA9 D11 / PB5 D4
* TIM4_CH3 PB8 D15/I2C / TIM4_CH4 PB9 D14/I2C
*/
vu16 PWM_Init(TIM_TypeDef *Timer, char Voie, float Frequence_PWM_hz);

/**
*configurer CCR correspondant avec un rapport cyclique entre 0 et 1
*il faut d'abord init ce pwm
**/
void PWM_set_Cycle(TIM_TypeDef *Timer, char Voie, float rapport_cyclique);

#endif 
