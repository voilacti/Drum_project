#include "feedback.h"
#include "gpio.h"
#include "timer.h"

void Feedback_Init(Timer_Channel timer_channel) {
	GPIO_TypeDef* port = Timer_AF_Remapping_Port[timer_channel];
	u8 pin = Timer_AF_Remapping_Pin[timer_channel];
	TIM_TypeDef* timer = Timer_Channel_To_Timer[timer_channel];
	u8 channel = Timer_Channel_To_Channel[timer_channel];
	
	GPIO_Config(port, pin, Output2MHz, AltPushPull);
	Timer_Set_PWM(timer, channel);
}

void Feedback_Set(Timer_Channel timer_channel, double intensity) {
	TIM_TypeDef* timer = Timer_Channel_To_Timer[timer_channel];
	u8 channel = Timer_Channel_To_Channel[timer_channel];
	Timer_Set_Duty_Cycle(timer, channel, intensity*intensity);
	Timer_Start(Timer_Channel_To_Timer[timer_channel], 5000);
}
