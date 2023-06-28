/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Receive data from MCU1 print the value to LCD screen
*/

#include "stm32f10x.h"
#include "delay.h"
#include "LCD.h"

#define RX GPIO_Pin_8
#define GPIOx GPIOA

GPIO_InitTypeDef gpio;
void config();

int main() {

	config();
	
  LCD_Init();
	
  uint8_t data = 0;
	
  while(1) {
		
		/* Check starting condition */
    if (GPIO_ReadInputDataBit(GPIOx, RX) == 0) {
		  delayUs(150);
		
	  	uint8_t j = 0;
			
			/* Receive data from array containing 4 values of MCU1*/
		  while (j < 4) {
			  data = 0;
			  for (int i = 0; i < 8; i++) {
		      if (GPIO_ReadInputDataBit(GPIOx, RX) == 1) data = data | (1 << i);
		  	  delayUs(104);
		    }
				
				/* Print value on the LCD */
		    LCD_PrintNumber(data);
		    LCD_SendString(" ");
		    j++;
	  	}
    }
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
	
  gpio.GPIO_Pin = RX;
  gpio.GPIO_Mode = GPIO_Mode_IPU;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &gpio);
	
	
	gpio.GPIO_Pin = GPIO_Pin_13;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &gpio);
}

