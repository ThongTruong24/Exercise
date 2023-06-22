/*
* File: I2CMater.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Here is the file that does generated to write the transmit and receive functions of the i2c standard
*/

#ifndef _I2CMater_H
#define _I2CMater_H

#define SCL DIO_CHANNEL_PB12
#define SDA DIO_CHANNEL_PB13

/* Function to convert sda pin to OUTPUT */
#define setOutputSDA() {\
	GPIOB->CRL &= ~(GPIO_CRH_MODE13 | GPIO_CRH_MODE13);\
    GPIOB->CRL |= GPIO_CRH_MODE13_0;\
	GPIOB->BSRR = GPIO_Pin_13;\
										   }

/* Function to convert sda pin to INPUT */
#define setInputSDA() {\
    GPIOB->CRL &= ~(GPIO_CRH_MODE13 | GPIO_CRH_MODE13);\
    GPIOB->CRL |= GPIO_CRH_MODE13_1;\
	GPIOB->BRR = GPIO_Pin_13;\
										  }

/* Address of slave */
#define slave1 0x56 

/* Set high status for scl and sda */
void setStatus();

/* The function implements the communication methods in order */
void I2C();

/* Transmit 7 bits of data to find the corresponding slave */
void transmit7BitAddress(uint8_t data);

/* Transmit 8 bits of data to the respective slave */
void transmitData(uint8_t data);

/* Receive 8 bits of data sent from slave */
uint8_t receiveData();

/* Set write state */
void transmitBitWrite();

/* Check the sda pin to see if the data previously transmitted  */
uint8_t checkACK();		

/* Set state level of scl and sda corresponding to initial condition */
void startCondition();

/* Set state level of scl and sda corresponding to end condition */
void endCondition();

/* Pulse setting for scl pin */
void SCLClock();


#endif