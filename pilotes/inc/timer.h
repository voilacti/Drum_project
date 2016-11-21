#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"
 
typedef void (*Timer_Handler)(void);

int Timer_Index(TIM_TypeDef *timer);
void Timer_Init(TIM_TypeDef *timer);
void Timer_Set_PWM(TIM_TypeDef *timer, u8 channel);
void Timer_Set_Duty_Cycle(TIM_TypeDef *timer, u8 channel, double duty_cycle);
void Timer_Set_Interrupt(TIM_TypeDef *timer, u8 priority, Timer_Handler handler);
double Timer_Start(TIM_TypeDef *timer, double freq);

/* Timer Alternate Function Remapping

TIM1 CH1 -> GPIOA pin 8
TIM1 CH2 -> GPIOA pin 9
TIM1 CH3 -> GPIOA pin 10
TIM1 CH4 -> GPIOA pin 11

TIM2 CH1 -> GPIOA pin 0
TIM2 CH2 -> GPIOA pin 1
TIM2 CH3 -> GPIOA pin 2
TIM2 CH4 -> GPIOA pin 3

TIM3 CH1 -> GPIOA pin 6
TIM3 CH2 -> GPIOA pin 7
TIM3 CH3 -> GPIOB pin 0
TIM3 CH4 -> GPIOB pin 1

TIM4 CH1 -> GPIOB pin 6
TIM4 CH2 -> GPIOB pin 7
TIM4 CH3 -> GPIOB pin 8
TIM4 CH4 -> GPIOB pin 9

*/

typedef enum Timer_Channel {
	TIM1_CH1, TIM1_CH2, TIM1_CH3, TIM1_CH4,
	TIM2_CH1, TIM2_CH2, TIM2_CH3, TIM2_CH4,
	TIM3_CH1, TIM3_CH2, TIM3_CH3, TIM3_CH4,
	TIM4_CH1, TIM4_CH2, TIM4_CH3, TIM4_CH4
} Timer_Channel;

static GPIO_TypeDef* Timer_AF_Remapping_Port[16];
static u8 Timer_AF_Remapping_Pin[16];
static TIM_TypeDef* Timer_Channel_To_Timer[16];
static u8 Timer_Channel_To_Channel[16];

#endif
