#ifndef FBUSER_H
#define FBUSER_H

#include "STM32F10X.h"
#include "pwm.h"
/*Example:
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    Init_ADC_Single_Conv(ADC1, 1) ;
	  Feedback_user_Init (4, 0);// Voie4
		while (1){
			data_adc=ADC_read_data(ADC1);
			intensite=(float)data_adc/0xFFF;
			Feedback_user_In(4, intensite);
    }
*/

/*ce feedback active Pin en alternet PushPull
* genere signal pwm sortie
* Voie:
    1 : TIM3_CH1 PB4 D5
    2 : TIM3_CH2 PB5 D4
		3 : TIM4_CH3 PB8 D15/I2C 
		4 : TIM4_CH4 PB9 D14/I2C
* Num_target: 
 (on fait rien dessus pour l'instant, 0 default) 
    0 pour non speciale, 
    1 2 reserve aux pieds,
    3 4 5 6 7 8 pour differents plaque
* Besoin avant d'utiliser
    RCC->APB1ENR |= RCC_APB2ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
* Config realise
    PB4 Alternate PP
    PWM init avec TIM3 freq 10
    Niv_Vibration intique niveau genere par pwm
*/
void Feedback_user_Init (char Voie, char Num_target);
/*Permet d'envoyer un pic de lumiere
* En fait, c'est un PWM_set_Cycle cache, avec un log de dans?
*/
void Feedback_user_In(char Voie, float Intensite);
/*But final:
* Tourner sans arret un programme qui fait varier rapport cyclique
* Penser a interruption
*/


#endif 
