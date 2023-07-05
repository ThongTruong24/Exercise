/*
* File: timer.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: config TIM2
*/

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "timer.h"
#include "spiReceive.h"

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
	 * TIM2 initialization for overflow every 1us
   * Update Event (Hz) = timer_clock / (TIM_Prescaler * Time_unit)
	 * Update Event (Hz) = 72MHz / (2 * 1000000) = 36Hz (1us)
   */
	TIM_TimeBaseInitStruct.TIM_Prescaler = 2;
	TIM_TimeBaseInitStruct.TIM_Period = 36;
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
		
		/* Data transmission detection condition*/
		if(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == SET) SPI_AssignNewData();
			
		/* Clears the TIM2 interrupt pending bit */
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
	}
}