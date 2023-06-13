#ifndef _DELAY_H
#define _DELAY_H

#include "stm32f10x.h"

void TIM2_INT_Init();
void delayMs(uint32_t ms);


#endif