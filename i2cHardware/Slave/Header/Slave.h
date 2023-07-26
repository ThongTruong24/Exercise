/*
* File: Slave.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: File definition of functions in file Slave.c
*/

#ifndef _Slave_H
#define _Slave_H

#include "stm32f10x.h"

/* Initialize I2C1 for Slave */
void I2C1_Init(void);

/* Check for ACK/NACK received from the master */
uint8_t I2C_CheckAckNack(void);

/* Wait for the slave address match and receiver mode */
uint8_t I2C1_WaitForAddress(void);

/* Receive data from the I2C bus */
void I2C_Receiver (uint8_t *receivedData, uint8_t length);

/* Transmit data to the I2C bus */
void I2C_Transmitter (uint8_t *receivedData, uint8_t length);

#endif