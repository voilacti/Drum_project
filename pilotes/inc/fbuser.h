#ifndef FBUSER_H
#define FBUSER_H

#include "STM32F10X.h"

/*ce feedback genere signal pwm sortie D5/TIM3_CH1/PB4
* Num_Target: 0 pour non speciale, 1 2 reserve aux pieds, 3+ pour differents plaque
* Niv_Vibration: 1 default, regler 0.~1. 
* 
*/
void feedback_user ( char Num_target, float Niv_vibration ){};



#endif 
