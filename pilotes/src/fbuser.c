#include "fbuser.h" 

#define FREQ_PWM 5000

void Feedback_user_Init (char Voie, char Num_target){
    if (Voie == 1){
      Port_IO_Init_Alter_PP(GPIOB,4);
			PWM_Init(TIM3,1,FREQ_PWM);
    }else if (Voie == 2){
      Port_IO_Init_Alter_PP(GPIOB,5);
			PWM_Init(TIM3,2,FREQ_PWM);
    }else if (Voie == 3){
      Port_IO_Init_Alter_PP(GPIOB,8);
			PWM_Init(TIM4,3,FREQ_PWM);
		}else if (Voie == 4){
      Port_IO_Init_Alter_PP(GPIOB,9);
			PWM_Init(TIM4,4,FREQ_PWM);
		}
    

}
void Feedback_user_In(char Voie, float Intensite){
	float lumino_eye = Intensite*Intensite;
	if ((Voie==1)||(Voie==2)){
		PWM_set_Cycle(TIM3, Voie, lumino_eye);
	}
	else if ((Voie==3)||(Voie==4)){
		PWM_set_Cycle(TIM4, Voie, lumino_eye);
	}
}
