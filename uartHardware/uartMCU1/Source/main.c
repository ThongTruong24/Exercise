/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Transmit and receive feedback data form MCU2, print data on LCD to check
*/

#include "stm32f10x.h"
#include "delay.h"
#include "LCD.h"
#include "uartMCU1.h"

int main (void) {
	
	/* Assuming the program is running other commands */
	delayMs(2000);
	
  USART1_Init();
	
	/* Data to transmit */
	uint8_t data = 1;

	while (1) {
	  
		/* Transmit and increase data by 1*/
    USART1_Send(data);
		data++;
			
    uint8_t dataReceive =  USART1_Receive();
		
		/*
		* The selected mode is even bit check, so the 8th bit is the check bit, 
		* the maximum data value received is 127 corresponding to 1111111 (7 bits 1)
		*/
	  dataReceive = dataReceive & 127;
			
    /* Check data on LCD */
		LCD_Init();
		LCD_PrintNumber(dataReceive);
	  delayMs(100);
  }
	
}


