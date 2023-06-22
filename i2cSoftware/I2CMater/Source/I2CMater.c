/*
* File: I2CMater.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: file that writes functions to implement I2C communication programs
*/

#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "I2CMater.h"

/*
* Function: I2C
* Description: The function implements the communication methods in order
* Input:
*   None
* Output:
*   None
*/
void I2C () {


		setStatus();
	  startCondition();
	  
		/* Transmit address with the corresponding slave */
	  transmit7BitAddress(slave1);

		/* Request write data from master */ 
	  transmitBitWrite();
	  
	  /* Check if the slave is receiving data */
	  setInputSDA();
	  if (checkACK() == 0) {
		  setOutputSDA();
		  SCLClock();
			
			/* Transfer data to be transmitted */
		  transmitData(40);
		} else return;
			
		setInputSDA();
	  if (checkACK() == 0) {
		  setOutputSDA();
		  SCLClock();
	  	transmitData(100);
		} else return;
		
		setInputSDA();
	  if (checkACK() == 0) {
		  setOutputSDA();
		} else return;
		
		/* End transmit and recive processing */
		endCondition();
		
}

/*
* Function: transmit7BitAddress
* Description: Transmit 7 bits of data to find the corresponding slave
* Input:
*   address: find slave with the transmitted address
* Output:
*   None
*/
void transmit7BitAddress (uint8_t address) {
	
  /* Transmt data when pulse is up */
	Dio_WriteChannel(SCL, STD_LOW);
	uint8_t i = 0;
	for( ; i < 7; i++) {
		
		/* 0x40: 1000000 
	  *  address = 0x56: 1010110
		* Bit shift with corresponding index to transmit data 
		*/
		if (address & (0x40 >> i)) Dio_WriteChannel(SDA, STD_HIGH);
		else Dio_WriteChannel(SDA, STD_LOW);
		
		/* transmit 1 clock pulse */
		SCLClock();
	}
}

/*
* Function: transmitData
* Description: Transmit 8 bits of data to the respective slave
* Input:
*   data: Data to be transmitted
* Output:
*   None
*/
void transmitData (uint8_t data) {

  uint8_t i = 0;
	for( ; i < 8; i++) {
		
		/* 0x80: 10000000
		* Bit shift with corresponding index to transmit data 
		*/
		if (data & (0x80 >> i)) Dio_WriteChannel(SDA, STD_HIGH);
		else Dio_WriteChannel(SDA, STD_LOW);
		
		/* transmit 1 clock pulse */
		SCLClock();
	}
	
}

/*
* Function: receiveData
* Description: Receive 8 bits of data sent from slave
* Input:
*   None
* Output:
*   data: Data is transmitted by slave
*/
uint8_t receiveData () {
 
	/* set pin SDA become INPUT */
	setInputSDA();
	uint8_t data = 0;
	uint8_t i = 0;
	
	for ( ; i < 8; i++) {
		
		/* Wait for the slave to change the sda pin state with the clock going down */
		SCLClock();
		if (Dio_ReadChannel(SDA) == 1) data = data | (1 << (7 - i));
	}
	/* set pin SDA become OUTPUT */
	setOutputSDA();
	return data;
}

/*
* Function: setStatus
* Description: Set high status for scl and sda
* Input:
*   None
* Output:
*   None
*/
void setStatus () {
	
	Dio_WriteChannel(SCL, STD_HIGH);
  Dio_WriteChannel(SDA, STD_HIGH);
	delayMs(50);
	
}

/*
* Function: transmitBitWrite
* Description: Set write state
* Input:
*   None
* Output:
*   None
*/
void transmitBitWrite() {
  
  Dio_WriteChannel(SDA, STD_HIGH);
	SCLClock();
	
}

/*
* Function: checkACK
* Description: Check the sda pin to see if the data previously transmitted 
* to the slave is received
* Input:
*   None
* Output:
*   1/0:
*     1: Received successfully
*     0: Receive failure
*/
uint8_t checkACK () {

	/* Check pin SDA */
	if (Dio_ReadChannel(SDA) == STD_LOW) return 0;
	else return 1;

}

/*
* Function: startCondition
* Description: Set state level of scl and sda corresponding to initial condition
* Input:
*   None
* Output:
*   None
*/
void startCondition () {
  
	Dio_WriteChannel(SDA, STD_LOW);
	delayMs(50);
	
}

/*
* Function: endCondition
* Description: Set state level of scl and sda corresponding to end condition
* Input:
*   None
* Output:
*   None
*/
void endCondition () {
	
  Dio_WriteChannel(SDA, STD_LOW);
	Dio_WriteChannel(SCL, STD_HIGH);
	delayMs(50);
	Dio_WriteChannel(SDA, STD_HIGH);
	
}

/*
* Function: SCLClock
* Description: Pulse setting for scl pin
* Input:
*   None
* Output:
*   None
*/
void SCLClock () {
  
	Dio_WriteChannel(SCL, STD_HIGH);
	delayMs(2);
	Dio_WriteChannel(SCL, STD_LOW);
	delayMs(2);

}