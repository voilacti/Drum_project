#ifndef PWM_H
#define PWM_H

#include "stm32f10x.h"
#include "clock.h"
#include "timer_1234.h"

/** 
* Configure l'PWM
* Il faut activer APB pont du timer et GPIO sortant
**/



/**In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
* else inactive.
**/
#define PWM_MODE_1 0b110


// Cette fonction initialise la voie specifie du timer voulu en PWM.
// La frequence souhaitee est passee en parametre.
// La fonction renvoie un entier qui correspond a la resolution de la PWM pour
// pouvoir ensuite regler les rapports cycliques.
//
// 3 Timer "general Purpose", TIM2, TIM3 et TIM4 + TIM1
// Chacun d'entre eux dispose de 4 voies de sorties numerotees de 1 a 4
// Mapping des IO:
// TIM1_CH1 - PA08 TM2_CH1_ETR - PA0 TM3_CH1 - PA6 TIM4_CH1 - PB6
// TIM1_CH1 - PA09 TM2_CH2 - PA1 TM3_CH2 - PA7 TIM4_CH2 - PB7
// TIM1_CH1 - PA10 TM2_CH3 - PA2 TM3_CH3 - PB0 TIM4_CH3 - PB8
// TIM1_CH4 - PA11 TM2_CH4 - PA3 TM3_CH4 - PB1 TIM4_CH4 - PB9
vu16 PWM_Init(TIM_TypeDef *Timer, char Voie, float Frequence_PWM_hz);

/**
*configurer CCR correspondant avec un rapport cyclique entre 0 et 1
*il faut d'abord init ce pwm
**/
void PWM_set_Cycle(TIM_TypeDef *Timer, char Voie, float rapport_cyclique);

#endif 
