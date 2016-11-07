#include "fbuser.h" 

void Feedback_user_Init (char Voie, char Num_target, float Niv_vibration){
    if (Voie == 1){
        Port_IO_Init_Alter_PP(GPIOB,4);
    }else if (Voie == 2){
        Port_IO_Init_Alter_PP(GPIOB,5);
    }
    
    /*20kHz pour la resolution d'un fichier son*/
    PWM_Init(TIM3,1,20000);
    PWM_set_Cycle(TIM3,1,Niv_vibration);

}

