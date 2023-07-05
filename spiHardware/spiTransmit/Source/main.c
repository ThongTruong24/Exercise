/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file is created to transmit array of data
*/

#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
#include "spiTransmit.h"


int main(void)
{

  SPI_Configuration();
	uint8_t data[] = {15, 34, 75, 64};

	while(1){
	  for (int i = 0; i < 4; i++) {

			/* Send data in turn */
	    SPI_SendData(data[i]);
  	}
  	data[1]++;

		/* After 0.5s the data array is sent 1 time */
  	delayMs(500);
	}
}