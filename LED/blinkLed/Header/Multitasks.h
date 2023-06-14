/*
* File: Multitasks.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Here is the file that does generated to write led blinking functions with tim2
*/

#ifndef _Multitasks_H
#define _Multitasks_H

#include "stm32f10x.h"

#define LEDPC13 Dio_FlipChannel(DIO_CHANNEL_PC13);

/* Init TIM2 */
void TIM2_INT_Init();

/* Reverse led */
void ledPC13();

/* Struct declaration includes led function pointer and delay limit value */
typedef struct {
	
  void (*led)();
	uint32_t limit;
	
} Task;


#endif