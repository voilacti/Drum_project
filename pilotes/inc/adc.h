#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"

typedef void (*ADC_Handler)(u16 data);

void ADC_Init(ADC_TypeDef* ADC);
void ADC_Set_Interrupt(ADC_TypeDef* ADC, u8 priority, ADC_Handler handler);
void ADC_Start(ADC_TypeDef* ADC);
int ADC_Data_Ready(ADC_TypeDef* ADC);
u16 ADC_Read(ADC_TypeDef* ADC);

#endif
