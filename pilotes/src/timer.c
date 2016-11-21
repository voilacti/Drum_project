#include "timer.h"
#include "clock.h"
#include "gpio.h"

Timer_Handler timer_handler[4];
static double PWM_duty_cycle[4][4];
static int is_PWM[4] = {0};

int Timer_Index(TIM_TypeDef *timer) {
	if (timer == TIM1) {
		return 0;
	} else if (timer == TIM2) {
		return 1;
	} else if (timer == TIM3) {
		return 2;
	} else if (timer == TIM4) {
		return 3;
	}
	
	return -1;
}

void Timer_Init(TIM_TypeDef *timer) {
	if (timer == TIM1) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	} else if (timer == TIM2) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	} else if (timer == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	} else if (timer == TIM4) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	
	timer->CR1 |= TIM_CR1_DIR;
}

void Timer_Set_PWM(TIM_TypeDef *timer, u8 channel) {
/**
if (Voie == 1){
        Timer->CCMR1 &= ~TIM_CCMR1_OC1M  ; // Mise à 0 du mode 
        Timer->CCMR1 |= (PWM_MODE_1)<< 4 ;//mode 110 : channel is active as long as TIMx_CNT<TIMx_CCR1
        Timer->CCMR1 |= TIM_CCMR1_OC1PE ;//enable preload
        Timer->CCER &= ~TIM_CCER_CC1P;//polarity active high
        Timer->CCER |= TIM_CCER_CC1E;
    }else if (Voie == 2){
        Timer->CCMR1 &= ~TIM_CCMR1_OC2M  ;
        Timer->CCMR1 |= (PWM_MODE_1) << 12 ;
        Timer->CCMR1 |= TIM_CCMR1_OC2PE ;
        Timer->CCER &= ~TIM_CCER_CC2P;
        Timer->CCER |= TIM_CCER_CC2E;
    }else if (Voie == 3){
        Timer->CCMR2 &= ~TIM_CCMR2_OC3M  ;
        Timer->CCMR2 |= (PWM_MODE_1)<< 4 ;
        Timer->CCMR2 |= TIM_CCMR2_OC3PE ;
        Timer->CCER &= ~TIM_CCER_CC3P;
        Timer->CCER |= TIM_CCER_CC3E;
    }else if (Voie == 4){
        Timer->CCMR2 &= ~TIM_CCMR2_OC4M ;
        Timer->CCMR2 |= (PWM_MODE_1)<< 12 ;
        Timer->CCMR2 |= TIM_CCMR2_OC4PE ;
        Timer->CCER &= ~TIM_CCER_CC4P;
        Timer->CCER |= TIM_CCER_CC4E;
}
*/
	/*timer->CCMR1 &= ~TIM_CCMR1_OC1M;
	timer->CCMR1 |= 0x6 << 4; // mode 110 
	timer->CCMR1 |= TIM_CCMR1_OC1PE; // enable preload
	timer->CCER &= ~TIM_CCER_CC1P; // polarity active high
	timer->CCER |= TIM_CCER_CC1E;
	*/
	timer->CCMR2 &= ~TIM_CCMR2_OC4M ;
    timer->CCMR2 |= 0x6 << 12 ;
    timer->CCMR2 |= TIM_CCMR2_OC4PE ;
    timer->CCER &= ~TIM_CCER_CC4P;
    timer->CCER |= TIM_CCER_CC4E;
		
	timer->CR1 |= TIM_CR1_ARPE;
	timer->EGR |= TIM_EGR_UG;
	
	is_PWM[Timer_Index(timer)] = 1;
	PWM_duty_cycle[Timer_Index(timer)][channel] = 0.0;
}

void Timer_Set_Duty_Cycle(TIM_TypeDef *timer, u8 channel, double duty_cycle) {
	PWM_duty_cycle[Timer_Index(timer)][channel] = duty_cycle;
}

void Timer_Set_Interrupt(TIM_TypeDef *timer, u8 priority, Timer_Handler handler) {
	if (timer == TIM1) {
		NVIC->ISER[0] |= NVIC_ISER_SETENA_25;
		NVIC->IP[25] = priority << 4;
	} else if (timer == TIM2) {
		NVIC->ISER[0] |= NVIC_ISER_SETENA_28;
		NVIC->IP[28] = priority << 4;
	} else if (timer == TIM3) {
		NVIC->ISER[0] |= NVIC_ISER_SETENA_29;
		NVIC->IP[29] = priority << 4;
	} else if (timer == TIM4) {
		NVIC->ISER[0] |= NVIC_ISER_SETENA_30;
		NVIC->IP[30] = priority << 4;
	}
	
	timer_handler[Timer_Index(timer)] = handler;
	timer->DIER |= TIM_DIER_UIE;
}

double Timer_Start(TIM_TypeDef *timer, double freq) {
	u32 ticks = CLOCK_GetTIMCLK(timer)/freq;
	timer->PSC = ticks / (1<<16);
	timer->ARR = ticks / (timer->PSC+1) - 1; 
	
	if (is_PWM[Timer_Index(timer)]) {
		timer->CCR1 = (timer->ARR+1) * PWM_duty_cycle[Timer_Index(timer)][0] - 1;
		timer->CCR2 = (timer->ARR+1) * PWM_duty_cycle[Timer_Index(timer)][1] - 1;
		timer->CCR3 = (timer->ARR+1) * PWM_duty_cycle[Timer_Index(timer)][2] - 1;
		timer->CCR4 = (timer->ARR+1) * PWM_duty_cycle[Timer_Index(timer)][3] - 1;
	}
	
	timer->CR1 |= TIM_CR1_CEN;
	
	return CLOCK_GetTIMCLK(timer) / ((timer->ARR+1)*(timer->PSC+1));
}

GPIO_TypeDef* Timer_AF_Remapping_Port[16] = {
	GPIOA, GPIOA, GPIOA, GPIOA,
	GPIOA, GPIOA, GPIOA, GPIOA,
	GPIOA, GPIOA, GPIOB, GPIOB,
	GPIOB, GPIOB, GPIOB, GPIOB
};

u8 Timer_AF_Remapping_Pin[16] = {
	8, 9, 10, 11,
	0, 1, 2, 3,
	6, 7, 0, 1,
	6, 7, 8, 9
};

TIM_TypeDef* Timer_Channel_To_Timer[16] = {
	TIM1, TIM1, TIM1, TIM1,
	TIM2, TIM2, TIM2, TIM2,
	TIM3, TIM3, TIM3, TIM3,
	TIM4, TIM4, TIM4, TIM4
};

u8 Timer_Channel_To_Channel[16] = {
	1, 2, 3, 4,
	1, 2, 3, 4,
	1, 2, 3, 4,
	1, 2, 3, 4
};

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

