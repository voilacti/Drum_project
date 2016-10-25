/**
  ******************************************************************************
  * @file    Timer_1234.c
  * @author  Quentin Leclerc & Nathan Balblanc
  * @date    16-September-2016
**/
#include "Timer_1234.h"

/** 
* Configure les Timers 1, 2, 3 et 4
* @param Timer Pointeur vers le jeu de registres (de type 
TIM_TypeDef
 ) du 
* timer considéré
* @param Duree_us Intervalle de temps exprimé en µs entre
* deux débordements successifs
* @return Le durée véritable qui a été configurée
**/
u32 Timer_1234_Init(TIM_TypeDef *Timer, u32 Frequence ) {
	
	u32 Clock, psc, arr , freq_interne;
	
	 // Enable du Timer concerné par le Init 
   if (Timer == TIM1) 
   {
         RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ;
   }
   else if (Timer == TIM2)   
   {  
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;    
   }
   else if (Timer == TIM3)   
   {  
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;    
   }
   else if (Timer == TIM4)   
   {  
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN ;    
   }  
   Timer->CR1 |= TIM_CR1_CEN ;
	
	Clock = CLOCK_GetTIMCLK(Timer) ; 
	// (1 << 16) = 65 536 = valeur max de la division Arr pour le maximiser

 	
	// Ex : 72 000 000 / 125 = 576 000 
	// 576 000 / 65 536 = 8,7 = 8 en entier
	// donc on veut 9, car avec 8 on aurait pas assez
	
	// Si ça tombe pas pile, alors on ajoute 1 
	// car en dessous c'est pas assez ! 
   freq_interne = Clock/Frequence;
   psc = freq_interne/65536;
   if ( (freq_interne % 65536) != 0) 
   {
         psc+= 1 ;
   }
   
   arr = Clock / Frequence / (psc) ;
  
   Timer->PSC = psc - 1 ; 
   Timer->ARR = arr - 1 ;

   return Clock / (psc*arr)  ; 
}

/** 
* Configure la routine d'interruption d'un Timer
* @param Timer Pointeur vers le jeu de registres (de type 
TIM_TypeDef
 ) du 
* timer considéré
* @param Priority Niveau de priorité de l'interruption
* @param IT_function Pointeur sur la fonction qui sera exécutée dans le routine
d'interruption
**/
void Timer_Active_IT(TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void)) {
   ptr_fonc = IT_function ;
   
   if (Timer == TIM2) 
      {
         NVIC->ISER[0] |= NVIC_ISER_SETENA_28 ;
         NVIC->IP[28] |= Priority << 4 ;
      }
   else if (Timer == TIM3) 
      { 
         NVIC->ISER[0] |= NVIC_ISER_SETENA_29 ;
         NVIC->IP[29] |= Priority << 4 ;
      }
   else if (Timer == TIM4) 
      {
         NVIC->ISER[0] |= NVIC_ISER_SETENA_30 ;
         NVIC->IP[30] |= Priority << 4 ;
      }
   else 
      {
         NVIC->ISER[0] |= NVIC_ISER_SETENA_25 ;
         NVIC->IP[25] |= Priority << 4 ;
      }
      Timer->DIER |= TIM_DIER_UIE ;
}


void TIM1_IRQHandler (void) {
   ptr_fonc() ;
   TIM1->SR &= ~(TIM_SR_UIF) ;
}

void TIM2_IRQHandler (void) {
   ptr_fonc() ;
   TIM2->SR &= ~(TIM_SR_UIF) ;
}

void TIM3_IRQHandler (void) {
   ptr_fonc() ;
   TIM3->SR &= ~(TIM_SR_UIF) ;
}

void TIM4_IRQHandler (void) {
   ptr_fonc() ;
   TIM4->SR &= ~(TIM_SR_UIF) ;
}



