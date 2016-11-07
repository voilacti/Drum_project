#ifndef GPIO_H
#define GPIO_H

#include "stm32f10x.h"

typedef enum Mode {
	Input = 0x0,
	Output10MHz = 0x4,
	Output2MHz = 0x8,
	Output50MHz = 0xf
} Mode;

typedef enum Config {
	Analog = 0x0,
	Floating = 0x1,
	PullUpPullDown = 0x2,
	Reserved = 0x3,
	GenPushPull = Analog,
	GenOpenDrain = Floating,
	AltPushPull = PullUpPullDown,
	AltOpenDrain = Reserved
} Config;

void GPIO_Init(GPIO_TypeDef* port);
void GPIO_Config(GPIO_TypeDef* port, u8 pin, Mode mode, Config config);
void GPIO_Set(GPIO_TypeDef* port, u8 pin);
void GPIO_Reset(GPIO_TypeDef* port, u8 pin);
void GPIO_Toggle(GPIO_TypeDef* port, u8 pin);
unsigned int GPIO_Read(GPIO_TypeDef* port, u8 pin);

#endif

