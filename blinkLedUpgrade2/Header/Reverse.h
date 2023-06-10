#ifndef _Reverse_H
#define _Reverse_H

#include "stm32f10x.h"

#define LEDPC13 Dio_FlipChannel(DIO_CHANNEL_PC13);
void TIM2_INT_Init();

typedef struct {
	
  void (*led)();
	uint32_t limit;
	
} Task;


#endif