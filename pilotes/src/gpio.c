#include "gpio.h"

void GPIO_Init(GPIO_TypeDef* port) {
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

void GPIO_Config(GPIO_TypeDef* port, u8 pin, Mode mode, Config config) {
	int bit = (pin%8)*4;
	
	if (pin < 8) {
		port->CRL &= ~(0xF << bit);
		port->CRL |= (mode|config) << bit;
	} else {
		port->CRH &= ~(0xF << bit);
		port->CRH |= (mode|config) << bit;
	}
}

void GPIO_Set(GPIO_TypeDef* port, u8 pin) {
	port->BSRR = 1 << pin;
}

void GPIO_Reset(GPIO_TypeDef* port, u8 pin) {
	port->BRR = 1 << pin;
}

void GPIO_Toggle(GPIO_TypeDef* port, u8 pin) {
	port->ODR ^= 1 << pin;
}

unsigned int GPIO_Read(GPIO_TypeDef* port, u8 pin) {
	return (port->IDR >> pin) & 1;
}
