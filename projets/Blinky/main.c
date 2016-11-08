

//____ registres de périphériques du stm_32
#include "stm32f10x.h"
#include "fbuser.h"
#include "adc.h"

u16 data_adc;
float intensite;
int main (void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    Init_ADC_Single_Conv(ADC1, 1) ;
	
	  Feedback_user_Init (4, 0);
	
		while (1){
			data_adc=ADC_read_data(ADC1);/*0-0xFFF*/
			intensite=(float)data_adc/0xFFF;/*0-1.*/
			Feedback_user_In(4, intensite);
    }
}

