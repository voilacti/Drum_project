#include "adc.h"
#include "clock.h"

ADC_Handler adc_handler[2];

void ADC_Init(ADC_TypeDef* ADC, u8 priority, ADC_Handler handler) {
	CLOCK_Configure();

	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		adc_handler[0] = handler;
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
		adc_handler[1] = handler;
	}
	
	ADC->CR2 |= ADC_CR2_ADON; // power on
	ADC->CR2 &= ~ADC_CR2_ALIGN; // align right
	ADC->CR1 |= ADC_CR1_EOCIE;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_18;
	NVIC->IP[18] = priority << 4;
	
	ADC->CR2 &= ~ADC_CR2_CONT; // single conversion
	ADC->SQR1 &= ~ADC_SQR1_L; // 1 conversion
	ADC->SQR3 &= ~ADC_SQR3_SQ1; // channel 0
}

void ADC_Start(ADC_TypeDef* ADC) {
	ADC->CR2 |= ADC_CR2_ADON;
}  

void ADC1_2_IRQHandler(void) {
	if (ADC1->SR & ADC_SR_EOC) {
		adc_handler[0](ADC1->DR);
	}
	if (ADC2->SR & ADC_SR_EOC) {
		adc_handler[1](ADC2->DR);
	}
}
