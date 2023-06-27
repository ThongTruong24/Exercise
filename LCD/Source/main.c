/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Display the word Successful connection!!! onto the LCD screen
*/

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
#include "LCD.h"

int main (void) {

  LCD_Init();
  
  LCD_SendString("Successful");
	
	/* 2nd line down */
	LCD_SendCmd(0xC0);
  delayUs(LCD_CMD_DELAY);
	
  LCD_SendString("connection!!!");
	
  while (1) {
		
		 /* Check */
     GPIO_SetBits(GPIOC, GPIO_Pin_13);
		 delayMs(100);
		 GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		 delayMs(100);
		
  }
}