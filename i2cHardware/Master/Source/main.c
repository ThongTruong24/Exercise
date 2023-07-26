/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Send data to Slave and get new data back
*/

#include "stm32f10x.h"
#include "LCD.h"
#include "delay.h"
#include "Master.h"

int main () {
	
  uint8_t dataArray[5] = {24, 68, 42, 82, 64};
	I2C1_Init();
	
	while(1) {
		
		I2C_Transmitter(48, dataArray, 5);
		I2C_Receiver(48, dataArray, 5);
    
		LCD_Init();
		for (uint8_t i = 0; i < 5; i++) {
      LCD_PrintNumber(dataArray[i]);
      LCD_SendString(" ");
			
		} 
	}
}