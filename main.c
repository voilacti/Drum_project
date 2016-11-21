#include <stm32f10x.h>
#include "adc.h"
#include "feedback.h"
#include "gpio.h"
#include "timer.h"
#include "clock.h"

void handler(void) {
	GPIO_Toggle(GPIOB, 14);
}

int main(void) {
	u16 tmp;
	CLOCK_Configure();
	GPIO_Init(GPIOB);
	Timer_Init(TIM4);
	Feedback_Init(TIM4_CH4);
	ADC_Init(ADC1);
	
	GPIO_Config(GPIOB, 14, Output10MHz, GenPushPull);
	Timer_Init(TIM2);
	Timer_Set_Interrupt(TIM2, 1, handler);
	Timer_Start(TIM2, 1);
	
	ADC_Start(ADC1);
	for(;;) {
		if (ADC_Data_Ready(ADC1)) {
			tmp = ADC_Read(ADC1);
			Feedback_Set(TIM4_CH1, (double)tmp/0xFFF);
			ADC_Start(ADC1);
		}
	}
}
