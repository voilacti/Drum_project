#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "stm32f10x.h"
#include "timer.h"

void Feedback_Init(Timer_Channel channel);
void Feedback_Set(Timer_Channel channel, double intensity);

#endif 
