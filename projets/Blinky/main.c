

//____ registres de périphériques du stm_32
#include "stm32f10x.h"
#include "pwm.h"


int main (void)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
    Port_IO_Init_Alter_PP(GPIOA,8);
    PWM_Init(TIM1,1,1);
    PWM_set_Cycle(TIM1,1,0.2);
    
  
	// TIM1 option speciale??
	
    
	while(1){}
}

