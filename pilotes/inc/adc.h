#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include "clock.h"

/** 
* Configure l'ADC
**/
void Init_ADC_Single_Conv(ADC_TypeDef * ADC) ;

u16 ADC_read_data(ADC_TypeDef * ADC, char channel);

#endif 
