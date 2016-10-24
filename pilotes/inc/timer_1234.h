// TRAVAIL DE LOIS LANO et RAMA DESPLATS
// gpio.h

#ifndef TIMER_1234_H
#define TIMER_1234_H

#include "stm32f10x.h"
 
typedef void (*)(void) Timer_Handler;
 
/**
* Configure les Timer 1, 2 ,3 et 4
* @param Timer Pointeur vers le jeu de registre (de type TIM_TypeDef) du
* timer considéré 
* @param Duree_us Intervalle de temps exprimé en microseconde entre
* deux débordements succesifs
* @return La Durée véritable qui a été configurée
**/

u32 Timer_1234_Init(TIM_TypeDef *timer, u32 duree_us);
void Timer_Active_IT(TIM_TypeDef *timer, u8 priority, Timer_Handler handler);

#endif