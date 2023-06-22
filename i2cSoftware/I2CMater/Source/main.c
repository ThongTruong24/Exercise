/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: I2C communication program
*/

#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "I2CMater.h"


GPIO_InitTypeDef gpio;
void configOutput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void config();

int main() {

	config();
	/* Initialize timer interrupt */
	TIM2_INT_Init();

  while(1){
		
	  I2C();
		
  }			
}

/*
* Function: configOutput
* Description: Configure Output
* Input:
*   GPIO_Pin: pin of gpio
*   GPIOx: GPIO A/B/C
* Output:
*   GPIO_Init: Initialize pin output of GPIO
*/	
void configOutput (uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx) {
	
  gpio.GPIO_Pin = GPIO_Pin;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOx, &gpio);
	
}

/*
* Function: config
* Description: Initialize the pins with the corresponding output functions
* Input:
*   None
* Output:
*   Configure pins
*/
void config() {
	
	/* GPIO clock for control and data lines */ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* Configure output */
  configOutput(GPIO_Pin_12, GPIOB);
  configOutput(GPIO_Pin_13, GPIOB);
	
}
