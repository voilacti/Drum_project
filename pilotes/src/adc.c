#include  "adc.h"

void Init_ADC_Single_Conv(ADC_TypeDef * ADC){
	
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN ;
	}
	else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ;
	}

	// Mise à 0 de CONT et activation ADON
	ADC->CR2 &= ~ ADC_CR2_CONT ;
	ADC->CR2 |= ADC_CR2_ADON ;
	ADC->SQR1 &= ~ADC_SQR1_L ; 
}


u16 ADC_read_data(ADC_TypeDef * ADC, char channel){

	u16 data = 0 ;
	
	// Mise de longueur à 1 pour single conv
	ADC->SQR1 &= ~ ADC_SQR1_L ;
	ADC->SQR1 |= ADC_SQR1_L_0 ;
	
	// Mise à 0 de la 1ère séquence 
	ADC->SQR3 &= ~ ADC_SQR3_SQ1 ; 
	// Set de channel dans la 1ère séquence
	ADC->SQR3 |= channel ;

	// On lance la conversion
	ADC->CR2 |= ADC_CR2_ADON ;

	// Tant que End Of Conversion n'est pas levé 
	while (~ (ADC->SR | ADC_SR_EOC) ) {}
		
	// On récupère la data  
	data = ADC->DR | ADC_DR_DATA ; 
	
	// Mise à 0 de EOC et STRT
	ADC->SR &= ~ (ADC_SR_STRT | ADC_SR_EOC) ;
		
	return data ; 
}  





