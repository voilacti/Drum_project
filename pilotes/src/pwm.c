#include "pwm.h"
#include "clock.h"
#include "timer.h"

#define PWM_MODE_1 0x6

void PWM_Init(TIM_TypeDef *timer, char channel) {
/// PAS TOUT A FAIT AU POINT (Loïs)
    Timer_Init(timer, 0, NULL);
    
    if (channel == 1) {
        timer->CCMR1 &= ~TIM_CCMR1_OC1M;
        timer->CCMR1 |= (PWM_MODE_1) << 4; // mode 110 
        timer->CCMR1 |= TIM_CCMR1_OC1PE; // enable preload
        timer->CCER &= ~TIM_CCER_CC1P; // polarity active high
        timer->CCER |= TIM_CCER_CC1E;
    } else if (channel == 2) {
        timer->CCMR1 &= ~TIM_CCMR1_OC2M ;
        timer->CCMR1 |= (PWM_MODE_1) << 12;
        timer->CCMR1 |= TIM_CCMR1_OC2PE;
        timer->CCER &= ~TIM_CCER_CC2P;
        timer->CCER |= TIM_CCER_CC2E;
    } else if (channel == 3) {
        timer->CCMR2 &= ~TIM_CCMR2_OC3M ;
        timer->CCMR2 |= (PWM_MODE_1) << 4;
        timer->CCMR2 |= TIM_CCMR2_OC3PE;
        timer->CCER &= ~TIM_CCER_CC2P;
        timer->CCER |= TIM_CCER_CC2E;
    } else if (channel == 4) {
        timer->CCMR2 &= ~TIM_CCMR2_OC4M;
        timer->CCMR2 |= (PWM_MODE_1)<< 12;
        timer->CCMR2 |= TIM_CCMR2_OC4PE;
        timer->CCER &= ~TIM_CCER_CC2P;
        timer->CCER |= TIM_CCER_CC2E;
    }
    
    timer->CR1 |= TIM_CR1_ARPE;
    timer->EGR |= TIM_EGR_UG;
    
    return resolution;
}

void PWM_Start(TIM_TypeDef *timer, char channel, u32 duree_us, float rapport_cyclique) {
	static u16* timerCCR[4] {
		&timer->CCR1,
		&timer->CCR2,
		&timer->CCR3,
		&timer->CCR4
	};
	
    Timer_Start(timer, duree_us);
    
    if (rapport_cyclique >= 1.0) {
        *timerCCR = 0xFFFF;
    } else {
        *timerCCR[channel-1] = (timer->ARR+1) * rapport_cyclique;
    }
}
