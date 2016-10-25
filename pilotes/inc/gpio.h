#ifndef GPIO_H
#define GPIO_H 

#include "STM32F10X.h"


char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche) ;
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche) ;
char Port_IO_Init_Alter_PP(GPIO_TypeDef * Port, u8 Broche) ;
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche) ;
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche) ;
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche) ;
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche) ;



#endif 
