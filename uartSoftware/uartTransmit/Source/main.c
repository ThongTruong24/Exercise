/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Perform data transmission with uart method
*/

#include "stm32f10x.h"
#include "delay.h"

#define TX GPIO_Pin_8
#define GPIOx GPIOA

GPIO_InitTypeDef gpio;
void config();

int main() {

	config();

	/* Data to be transmitted */
  uint8_t data[] = {162, 45, 86, 123};
	
  while(1) {
		
		/* Default state */
		GPIO_SetBits(GPIOx, TX);
		
		/* Other process of the program */
		delayMs(4000);
		
		/* Starting condition */
		GPIO_ResetBits(GPIOx, TX);
		
		/* baud rate 9600
    * 1 bit ~ 104 us
		*/
		
		delayUs(104);
		
		uint8_t j = 0;
		while (j < 4) {
			
		  for (int i = 0; i < 8; i++) {
	      if (data[j] & (1 << i)) GPIO_SetBits(GPIOA, TX);
			  else GPIO_ResetBits(GPIOx, TX);
			  delayUs(104);
		  }
			j++;
			
			/* Wait for MCU2 to display the value on LCD */
			delayUs(370);
		}
		/* Status ending */
		GPIO_SetBits(GPIOx, TX);
	}
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	
  gpio.GPIO_Pin = TX;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &gpio);
	
	
	gpio.GPIO_Pin = GPIO_Pin_13;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &gpio);
}