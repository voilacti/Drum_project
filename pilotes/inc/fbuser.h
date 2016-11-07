#ifndef FBUSER_H
#define FBUSER_H

#include "STM32F10X.h"
#include "pwm.h"

/*ce feedback genere signal pwm sortie
* Voie:
    1 : TIM3_CH1/PB4 D5
    2 : TIM3_CH2/PB5 D4
* Num_target: (on fait rien dessus pour l'instant) 
    0 pour non speciale, 
    1 2 reserve aux pieds,
    3 4 5 6 7 8 pour differents plaque
* Niv_vibration: 
    regler 0.~1., ie rapport_cyclique dans pwm

* Besoin avant d'utiliser
    RCC->APB1ENR |= RCC_APB2ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
* Config realise
    PB4 Alternate PP
    PWM init avec TIM3 freq 10
    Niv_Vibration intique niveau genere par pwm
*/
/*apres init
* 
*
*/
void Feedback_user_Init (char Voie, char Num_target, float Niv_vibration);



#endif 
