#ifndef _Multitasks_H
#define _Multitasks_H

#include "stm32f10x.h"

#define LEDPC13 Dio_FlipChannel(DIO_CHANNEL_PC13);
void TIM2_INT_Init();
void ledPC13();

typedef struct {
	
  void (*led)();
	uint32_t limit;
	
} Task;


#endif