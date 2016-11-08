#include "stm32f10x.h"

// How it works? 
/* Tout d'abord il faut configurer le CLOCK de l'adc ( il ne sert pas à grand chose dans le sens où
*on va lancer les acquisitions quand on veut ( on peut par exemple le faire par interruption associé à un timer)
* 
*
*
*/

#include  "adc.h"

void Init_ADC_Single_Conv(ADC_TypeDef * ADC, char channel){
	
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN ;
	}
	else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ;
	}

	// Mise à 0 de CONT et activation ADON
	ADC->CR2 &= ~ ADC_CR2_CONT ; 		// Single conversion Mode  (à 0)
	ADC->CR2 |= ADC_CR2_ADON ; 			// Allume l'ADC
	ADC->SQR1 &= ~ADC_SQR1_L ;  		// Channel sequence Length 0=1conversion
	
	// Mise de longueur à 1 pour single conv
	ADC->SQR1 &= ~ ADC_SQR1_L ;			//0=1Conversion		
	
	// Mise à 0 de la 1ère séquence 
	ADC->SQR3 &= ~ ADC_SQR3_SQ1 ; 
	// Set de channel dans la 1ère séquence
	ADC->SQR3 |= channel ;

}


u16 ADC_read_data(ADC_TypeDef * ADC){

	u16 data = 0 ;
	
	// On lance la conversion
	ADC->CR2 |= ADC_CR2_ADON ;

	// Tant que End Of Conversion n'est pas levé 
	while ((ADC->SR & ADC_SR_EOC)==0) {}
		 // 
	// On récupère la data  
	data = ADC->DR  ; 
	
	// Mise à 0 de EOC et STRT
	ADC->SR &= ~ (ADC_SR_STRT | ADC_SR_EOC) ;
		
	return data ; 
}  
