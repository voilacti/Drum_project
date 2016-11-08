#include "gpio.h" 


char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche) {	 
	if (Broche <= 7) {
		Port->CRL &=  ~(0xF << Broche*4) ;
		Port->CRL |= (0x4 << Broche*4) ; 	
	}
	else {
		Broche -= 8 ;
		Port->CRH &=  ~(0xF << (Broche*4)) ;
		Port->CRH |=  (0x4 << (Broche*4)) ; 	
	}
	return 0 ;
}

char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche) {
	if (Broche <= 7) {
		Port->CRL &= ~(0xF << (Broche*4)) ;
		Port->CRL |= (0x1 << (Broche*4)) ; 	
	}
	else {
		Broche-= 8 ;
		Port->CRH &= ~(0xF << (Broche*4)) ;
		Port->CRH |= (0x1 << (Broche*4)) ; 	
	}
	return 0 ;
}


char Port_IO_Init_Alter_PP(GPIO_TypeDef * Port, u8 Broche){
	if (Broche <= 7) {
		Port->CRL &= ~(0xF << (Broche*4)) ;
		Port->CRL |= (0x9 << (Broche*4)) ; 	
	}
	else {
		Broche-= 8 ;
		Port->CRH &= ~(0xF << (Broche*4)) ;
		Port->CRH |= 0x9 << (Broche*4) ; 	
	}
	return 0 ;
}


void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche) {
	Port->ODR = Port->ODR & (0x01 << Broche) ;
} 

void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche) {
	Port->BSRR = Port->BSRR & (0x01 << (Broche+16) ) ;
}

void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche) {
   Port->ODR ^= (0x01 << Broche);
}

unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche) {
	return (Port->IDR >> Broche) & 0x01 ;
}
