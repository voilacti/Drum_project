#include  "pwm.h"


vu16 PWM_Init(TIM_TypeDef *Timer, char Voie, float Frequence_PWM_hz){
    //u32 freq = Timer_1234_Init( Timer, Frequence_PWM_Khz ) ;
    vu16 resolution;
    //Timer_1234_Init(Timer, Frequence_PWM_Khz*1000 );
    Timer_1234_Init(Timer, Frequence_PWM_hz );
    resolution = Timer->ARR + 1;
    
    if (Voie == 1){
        Timer->CCMR1 &= ~TIM_CCMR1_OC1M  ;
        Timer->CCMR1 |= (PWM_MODE_1)<< 4 ;//mode 110 
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
        Timer->CCER &= ~TIM_CCER_CC2P;
        Timer->CCER |= TIM_CCER_CC2E;
    }else if (Voie == 4){
        Timer->CCMR2 &= ~TIM_CCMR2_OC4M ;
        Timer->CCMR2 |= (PWM_MODE_1)<< 12 ;
        Timer->CCMR2 |= TIM_CCMR2_OC4PE ;
        Timer->CCER &= ~TIM_CCER_CC2P;
        Timer->CCER |= TIM_CCER_CC2E;
    }
    
    Timer->CR1 |= TIM_CR1_ARPE;
    Timer->EGR |= TIM_EGR_UG;
    
    return resolution;
}

void PWM_set_Cycle(TIM_TypeDef *Timer, char Voie, float rapport_cyclique){
    u16 ccr_voulu;
    
    if (rapport_cyclique >= 1.0){
        ccr_voulu =0xFFFF;
    }else{
        ccr_voulu = (Timer->ARR +1) * rapport_cyclique;
    }
    
    if (Voie == 1){
        Timer->CCR1 = ccr_voulu;
    }else if (Voie == 2){
        Timer->CCR2 = ccr_voulu;
    }else if (Voie == 3){
        Timer->CCR3 = ccr_voulu;
    }else if (Voie == 4){
        Timer->CCR4 = ccr_voulu;
    }
        
}

