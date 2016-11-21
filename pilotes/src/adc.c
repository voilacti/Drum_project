#include "adc.h"
#include "clock.h"

ADC_Handler adc_handler[2];

void ADC_Init(ADC_TypeDef* ADC) {
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
	
	ADC->CR2 |= ADC_CR2_ADON; // power on
	ADC->CR2 &= ~ADC_CR2_ALIGN; // align right
	ADC->CR2 &= ~ADC_CR2_CONT; // single conversion
	ADC->SQR1 &= ~ADC_SQR1_L; // 1 conversion
	ADC->SQR3 &= ~ADC_SQR3_SQ1; // channel 0
}

void ADC_Set_Interrupt(ADC_TypeDef* ADC, u8 priority, ADC_Handler handler) {
	if (ADC == ADC1) {
		adc_handler[0] = handler;
	} else if (ADC == ADC2) {
		adc_handler[1] = handler;
	}
	
	NVIC->ISER[0] |= NVIC_ISER_SETENA_18;
	NVIC->IP[18] = priority << 4;
	ADC->CR1 |= ADC_CR1_EOCIE;
}

void ADC_Start(ADC_TypeDef* ADC) {
	ADC->CR2 |= ADC_CR2_ADON;
}

int ADC_Data_Ready(ADC_TypeDef* ADC) {
	return ADC->SR & ADC_SR_EOC;
}

u16 ADC_Read(ADC_TypeDef* ADC) {
	ADC->SR &= ~ADC_SR_STRT;
	return ADC->DR;
}

void ADC1_2_IRQHandler(void) {
	if (ADC1->SR & ADC_SR_EOC) {
		adc_handler[0](ADC1->DR);
	}
	if (ADC2->SR & ADC_SR_EOC) {
		adc_handler[1](ADC2->DR);
	}
}
