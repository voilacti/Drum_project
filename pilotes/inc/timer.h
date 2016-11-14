#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"
 
typedef void (*Timer_Handler)(void);

void Timer_Init(TIM_TypeDef *timer, u8 priority, Timer_Handler handler);
u32 Timer_Start(TIM_TypeDef *timer, u32 duree_us);

#endif
