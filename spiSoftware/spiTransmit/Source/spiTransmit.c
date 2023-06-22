/*
* File: spiTransmit.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Write functions that perform data transfer
*/

#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "spiTransmit.h"

/*
* Function: spiInit
* Description: Set the initial state for the pins
* Input:
*   None
* Output:
*   None
*/
void spiInit () {
	
	Dio_WriteChannel(SCK, STD_LOW);
	Dio_WriteChannel(MOSI, STD_LOW);
  Dio_WriteChannel(SS, STD_HIGH);
	
}

/*
* Function: clock
* Description: Set the transmitted clock signal
* Input:
*   None
* Output:
*   None
*/
void clock () {
	
  Dio_WriteChannel(SCK, STD_HIGH);
	delayMs(50);
	Dio_WriteChannel(SCK, STD_LOW);
	delayMs(50);
	
}

/*
* Function: transmit
* Description: Transmit data by setting the corresponding output levels of the SS, MOSI and SCK pins
* Input:
*   data: Data to be transmitted
* Output:
*   None
*/
void transmit (uint8_t data) {

	/* Data transmission start signal */
	Dio_WriteChannel(SS, STD_LOW);
  uint8_t i = 0;
	for ( ; i < 8; i++) {
		
		/* data = 162: 10100010
		* Check the left to right bits of the data to be transmitted and set the corresponding MOSI pin state 
		*/
	  if (data & (0x80 >> i)) Dio_WriteChannel(MOSI, STD_HIGH);
		else Dio_WriteChannel(MOSI, STD_LOW);
    
		/* Transmit 1 clock pulse to transmit the corresponding 1 bit */
		clock();
	}
	
	/* Data transmission end signal */
	Dio_WriteChannel(SS, STD_HIGH);
	
}