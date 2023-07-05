/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file is created to receive array of data
*/

#include "stm32f10x.h"
#include "delay.h"
#include "LCD.h"
#include "spiReceive.h"
#include "timer.h"

uint8_t receiveData[4];

int main(void) {
	
	SPI_Configuration();
	TIM2_INT_Init();

	/* This variable is used to check if new data has been received */
	uint8_t checkPrint = receiveData[1];
	
  while(1){
		
		/*
		* Conditions when receiving new data
		* The process takes place every 0.5s (set from the MASTER)
		*/
    if (checkPrint != receiveData[1]) {
		  
			LCD_Init();
		  for (int i = 0; i < 4; i++) {
				
				/* Print data array on LCD  */
	      LCD_PrintNumber(receiveData[i]);
		    LCD_SendString(" ");
			}
			checkPrint = receiveData[1];
			
	  }
  }
}
