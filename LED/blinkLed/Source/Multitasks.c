/*
* File: Multitasks.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: File generated to write led blinking functions with tim2
*/

#include "Dio.h"
#include "Multitasks.h"

/* millis counter variable */
uint32_t milliSec = 0;

/*
* Function: multitasks
* Description: Reverse led pin pc13
* Input:
*   Task *task: pointer of task struct 
* Output:
*   Reverse led pin pc13
*/
void multitasks (Task *task) {
	
  milliSec = 0;
	while (milliSec <= task->limit);
  task->led();
	
}

/*
* Function: TIM2_INT_Init
* Description: Init TIM2
* Input:
*   Node
* Output:
*   Enable TIM2 interrupt
*   Start TIM2
*/
void TIM2_INT_Init()
{
  
	/* Init struct */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/* Enable clock for TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
	/* 
	 * TIM2 initialization for overflow every 1ms
   * Update Event (Hz) = timer_clock / (TIM_Prescaler * Time_unit)
	 * Update Event (Hz) = 72MHz / (3600 * 1000) = 20Hz (1ms)
   */
	TIM_TimeBaseInitStruct.TIM_Prescaler = 3600;
	TIM_TimeBaseInitStruct.TIM_Period = 19;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	/* Enable TIM2 interrupt */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	/* Start TIM2 */
	TIM_Cmd(TIM2, ENABLE);
	
  /* Nested vectored interrupt settings */
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
}

void TIM2_IRQHandler () {
	
	/* Checks whether the TIM2 interrupt has occurred or not */
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)) {
		
		/* millis counter */
		milliSec++;
		
		/* Clears the TIM2 interrupt pending bit */
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
	}
}

void ledPC13 () {
  LEDPC13;
}