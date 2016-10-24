#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include "clock.h"

typedef void (*)(u16 data) ADC_Handler;

void Init_ADC(ADC_TypeDef* ADC, u8 priority, ADC_Handler handler);
void ADC_Start(ADC_TypeDef* ADC);

#endif