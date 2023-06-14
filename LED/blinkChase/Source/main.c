/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Blinking and chasing with 8 LED
*/

#include "stm32f10x.h"
#include "delay.h"
#include "blinkChase.h"

GPIO_InitTypeDef gpio;
void configInput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void configOutput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void config();

int main() {

  config();
	
	/* Initialize timer interrupt */
	TIM2_INT_Init();

  while(1) {
		
		/* Test and execute the button 1 and button 2 */
	  butTon1();
	  butTon2();

  }
}

/*
* Function: configInput
* Description: Configure Input
* Input:
*   GPIO_Pin: pin of gpio
*   GPIOx: GPIO A/B/C
* Output:
*   GPIO_Init: Initialize pin input of GPIO
*/
void configInput (uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx) {
	
  gpio.GPIO_Pin = GPIO_Pin;
  gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOx, &gpio);
	
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
* Description: Initialize the pins with the corresponding input/output functions
* Input:
*   None
* Output:
*   Configure pins
*/
void config() {
 	
	/* GPIO clock for control and data lines */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
	/* Configure I/O */
  configInput(GPIO_Pin_12, GPIOB);
  configInput(GPIO_Pin_13, GPIOB);
  configInput(GPIO_Pin_14, GPIOB);
		
  configOutput(GPIO_Pin_15, GPIOB);
  configOutput(GPIO_Pin_8, GPIOA);
  configOutput(GPIO_Pin_9, GPIOA);
  configOutput(GPIO_Pin_10, GPIOA);
  configOutput(GPIO_Pin_11, GPIOA);
  configOutput(GPIO_Pin_12, GPIOA);
  configOutput(GPIO_Pin_6, GPIOB);
  configOutput(GPIO_Pin_7, GPIOB);
	
}
	


