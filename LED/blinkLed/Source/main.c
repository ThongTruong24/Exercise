/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Blinking led at pc13 pin
*/

#include "stm32f10x.h"
#include "Multitasks.h"


GPIO_InitTypeDef gpioPC13;
void config();

int main (void) {

	config();
	
	/* Initialize timer interrupt */
	TIM2_INT_Init();
	
	
  /* Declare tasks; */
	Task task1 = {&ledPC13, 600};
	Task task2 = {&ledPC13, 100};
	
	while (1) {
		
		/* Blinking led */
    multitasks(&task1);
		multitasks(&task2);
		
	}
}


void config () {

	/* Initialize PC13 as push-pull output for LED */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioPC13.GPIO_Pin = GPIO_Pin_13;
	gpioPC13.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioPC13.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpioPC13);
	
}
