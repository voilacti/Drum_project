#include "timer.h"
#include "clock.h"
#include "gpio.h"

Timer_Handler timer_handler[4];

void Timer_Init(TIM_TypeDef *timer, u8 priority, Timer_Handler handler) {
	CLOCK_Configure();
    
    if (timer == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		NVIC->ISER[0] |= NVIC_ISER_SETENA_25;
		NVIC->IP[25] = priority << 4;
        timer_handler[0] = handler;
    } else if (timer == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		NVIC->ISER[0] |= NVIC_ISER_SETENA_28;
		NVIC->IP[28] = priority << 4;
        timer_handler[1] = handler;
	} else if (timer == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		NVIC->ISER[0] |= NVIC_ISER_SETENA_29;
		NVIC->IP[29] = priority << 4;
        timer_handler[2] = handler;
	} else if (timer == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		NVIC->ISER[0] |= NVIC_ISER_SETENA_30;
		NVIC->IP[30] = priority << 4;
        timer_handler[3] = handler;
	}
    
	timer->CR1 |= TIM_CR1_DIR;
	timer->DIER |= TIM_DIER_UIE;
}

u32 Timer_Start(TIM_TypeDef *timer, u32 duree_us) {
	u32 ticks = ((CLOCK_GetTIMCLK(timer)/1000000) * duree_us);
	timer->PSC = ticks/(1 << 16);
	timer->ARR = ticks/(timer->PSC+1) - 1; 
	
	timer->CR1 |= TIM_CR1_CEN;
	
	return (timer->ARR+1)*(timer->PSC+1);
}

void TIM1_IRQHandler(void) {
	timer_handler[0]();
	TIM1->SR &= ~TIM_SR_UIF;
}

void TIM2_IRQHandler(void) {
	timer_handler[1]();
	TIM2->SR &= ~TIM_SR_UIF;
}

void TIM3_IRQHandler(void) {
	timer_handler[2]();
	TIM3->SR &= ~TIM_SR_UIF;
}

void TIM4_IRQHandler(void) {
	timer_handler[3]();
	TIM4->SR &= ~TIM_SR_UIF;
}
