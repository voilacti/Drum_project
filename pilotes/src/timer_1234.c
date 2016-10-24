//__________________________________________________________
// BINOME : LANO - DESPLATS
// ETAT : 
//__________________________________________________________

//____ registres de périphériques du stm_32
#include "stm32f10x.h"
#include "clock.h"
#include "gpio.h"
#include "timer_1234.h"

Timer_Handler timer_handler[4];

/**
* Configure la routine d'interruption d'un timer
* @param timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer considéré
* @param priority Niveau de priorite´ de l'interruption
* @param IT_function Pointeur sur la fonction qui sera exe´cute´e dans le routine d'interruption
**/
void Timer_Active_IT(TIM_TypeDef *timer, u8 priority, Timer_Handler handler) {
    if (timer == TIM1){
		NVIC->ISER[0] |= NVIC_ISER_SETENA_25;
		NVIC->IP[25] = priority << 4;
        timer_handler[0] = handler;
    } else if (timer == TIM2){
		NVIC->ISER[0] |= NVIC_ISER_SETENA_28;
		NVIC->IP[28] = priority << 4;
        timer_handler[1] = handler;
	} else if (timer == TIM3){
		NVIC->ISER[0] |= NVIC_ISER_SETENA_29;
		NVIC->IP[29] = priority << 4;
        timer_handler[2] = handler;
	} else if (timer == TIM4){
		NVIC->ISER[0] |= NVIC_ISER_SETENA_30;
		NVIC->IP[30] = priority << 4;
        timer_handler[3] = handler;
	}
    
	timer->DIER |= TIM_DIER_UIE;
}

u32 Timer_1234_Init(TIM_TypeDef *timer, u32 duree_us) {
	CLOCK_Configure();
    
	//Activer les clocks
    if (timer == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    } else if (timer == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	} else if (timer == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	} else if (timer == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
    
	//enable clock dans AP bridge 1
	timer->CR1 |= TIM_CR1_CEN | TIM_CR1_DIR; //Chip Enable du timer et le mettre en décomptage

	// CLOCK_GetTIMCLK(timer)*(duree_us/1000000) //permet de récupérer la fréq du clock AH
	u32 nb_ticks = ((CLOCK_GetTIMCLK(timer)/1000000) * duree_us); //On divise par 1000000 car la durée est en us
	timer->PSC = nb_ticks/(1 << 16); //valeur max d'ARR : 65536	
	timer->ARR = nb_ticks/(timer->PSC+1); 
	
	return timer->ARR*(timer->PSC+1); //durée véritablement configurée
}

void TIM1_IRQHandler(void) {
	timer_handler[0]();
	TIM1->SR &= ~TIM_SR_UIF;
}

void TIM2_IRQHandler(void) {
	timer_handler[1]();
	TIM2->SR &= ~TIM_SR_UIF;
}

void TIM3_IRQHandler(void) {
	timer_handler[2]();
	TIM3->SR &= ~TIM_SR_UIF;
}

void TIM4_IRQHandler(void) {
	timer_handler[3]();
	TIM4->SR &= ~TIM_SR_UIF;
}