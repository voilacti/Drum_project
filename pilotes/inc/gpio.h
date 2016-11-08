//configurer une broche d'un port en output push-pull (CNFO ET MODE = 0101 = A ) 
char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche);

//Configuration en floating input code = 0x4
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche);

//Configuration en analog input code = 0x4
char Port_IO_Init_Analog_input( GPIO_TypeDef * Port, u8 Broche);

//Configuration en Alternate function output 
char Port_IO_Init_Alter_PP(GPIO_TypeDef * Port, u8 Broche);

//Set la broche à 1 on utilise BSRR
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche);

//Reset la broche on utilise BRR
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche);

//Inverser l'etat d'une broche
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche);

//Lire un état 
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche);
