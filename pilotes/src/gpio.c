// TRAVAIL DE LOIS LANO et RAMA DESPLATS
// gpio.h

#include "gpio.h"

void Port_IO_Init(GPIO_TypeDef* port) {
    if (port == GPIOA) {
        RCC->APB2ENR = RCC_APB2ENR_IOPAEN;
    } else if (port == GPIOB) {
        RCC->APB2ENR = RCC_APB2ENR_IOPBEN;
    } else if (port == GPIOC) {
        RCC->APB2ENR = RCC_APB2ENR_IOPCEN;
    } else if (port == GPIOD) {
        RCC->APB2ENR = RCC_APB2ENR_IOPDEN;
    }
}

void Port_IO_Init_Output(GPIO_TypeDef* port, u8 broche) {
	int bit = (broche%8)*4;
	Port_IO_Init(port);
	
	if (broche < 8) {
		port->CRL &= ~(0xF << bit);
		port->CRL |= 1 << bit;
	} else {
		port->CRH &= ~(0xF << bit);
		port->CRH |= 1 << bit;
	}
}

void Port_IO_Init_Input(GPIO_TypeDef* port, u8 broche) {
	int bit = (broche%8)*4;
	Port_IO_Init(port);
	
	if (broche < 8) {
		port->CRH &= ~(0xF << bit);
		port->CRL |= 1 << (bit+2);
	} else {
		port->CRH &= ~(0xF << bit);
		port->CRH |= 1 << (bit+2);
	}
}

void Port_IO_Set(GPIO_TypeDef* port, u8 broche) {
	port->BSRR = 1 << broche;
}

void Port_IO_Reset(GPIO_TypeDef* port, u8 broche) {
	port->BRR = 1 << broche;
}

void Port_IO_Blink(GPIO_TypeDef* port, u8 broche) {
	port->ODR ^= 1 << broche;
}

unsigned int Port_IO_Read(GPIO_TypeDef* port, u8 broche) {
	return (port->IDR >> broche) & 1;
}




































#include "gpio.h"

void Port_IO_Init(GPIO_TypeDef* port){
    if(port == GPIOA)
        RCC->APB2ENR |= RCC_APB2_ENR_IOPAEN;
    else if(port == GPBIOB)
        RCC->APB2ENR |= RCC_APB2_ENR_IOPBEN;
    else
        RCC->APB2ENR |= RCC_APB2_ENR_IOPCEN;
}

void Port_IO_Init_Output(GPIO_TypeDef* port, u8 broche){
    int bit = (broche%8)*4; //modulo les 8 bits par CRL/CRH *4 bits si bit 1
    if(bit < 8){
        port->CRL &= ~(0xF) << bit; //car 0xF = 1111
        port->CRL |= (1<<bit);
    }else {
        port->CRH &= ~(0xF) << bit; //car 0xF = 1111
        port->CRH |= (1<<bit);
    }
}
        
void Port_IO_Init_Input(GPIO_TypeDef* port, u8 broche){
    int bit = (broche%8)*4;
    if (bit<8){
        port->CRL &= ~(0xF) << bit;
        port->CRL |= (1 << (bit+2);
    }else{
        port->CRL &= ~(0xF) << bit;
        port->CRL |= (1 << (bit+2);
    }
}

void Port_IO_Set(GPIO_TypeDef* port, u8 broche){
    port->A
