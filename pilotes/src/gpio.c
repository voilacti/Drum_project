#include "stm32f10x.h"

//configurer une broche d'un port en output push-pull (CNFO ET MODE = 0010 = 2 ) 
char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche){
	int masque;
	if (Broche>7){ //high
		Broche=Broche-8;
		masque = ~(0xF << (Broche*4));
		Port->CRH= masque & (Port->CRH);
		Port->CRH= Port->CRH | (0x2<<(Broche*4));
	}
	//LOWPort->
	else {
		masque = ~(0xF << (Broche*4));
		Port->CRL= masque & (Port->CRL);
		Port->CRL= Port->CRL | (0x2<<(Broche*4));
	}
	return '0';
}

//Configuration en floating input code = 0x4
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche){
	int masque;
	if (Broche>7){ //high
		Broche=Broche-8;
		masque = ~(0xF << (Broche*4));
		Port->CRH= masque & (Port->CRH);
		Port->CRH= Port->CRH | (0x4<<(Broche*4));
	}
	//LOWPort->
	else {
		masque = ~(0xF << (Broche*4));
		Port->CRL= masque & (Port->CRL);
		Port->CRL= Port->CRL | (0x4<<(Broche*4));
	}
	return '0';
}

//configure la broche en sortie AlternateFunction
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

char Port_IO_Init_Analog_input( GPIO_TypeDef * Port, u8 Broche) {
	int masque;
	if (Broche>7){ //high
		Broche=Broche-8;
		masque = ~(0xF << (Broche*4));
		Port->CRH= masque & (Port->CRH);
		Port->CRH= Port->CRH | (0x0<<(Broche*4));
	}
	//LOWPort->
	else {
		masque = ~(0xF << (Broche*4));
		Port->CRL= masque & (Port->CRL);
		Port->CRL= Port->CRL | (0x0<<(Broche*4));
	}
	return '0';
}

//Set la broche à 1 on utilise BSRR
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche){
		Port->BSRR = (0x1 << Broche);
}

//Reset la broche on utilise BRR
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche){
		Port->BRR = (0x1 << Broche);
}

//Inverser l'etat d'une broche
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche){
	int masque= (0x1 << Broche);
	if( (Port->ODR & masque)>>Broche){
		Port_IO_Reset(Port,Broche);
	}
	else{
		Port_IO_Set(Port,Broche);
	}
}

unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche){
	
	return (((Port->IDR)&(0x1<<Broche))>>Broche);
}
