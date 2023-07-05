/*
* File: spiReceive.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This is the file used to define SPI constructors and data transfer
*/

#ifndef _SPIRECEIVE_H
#define _SPIRECEIVE_H

#include "stm32f10x.h"

/* Config SPI */
void SPI_Configuration(void);

/* Receive data */
uint8_t SPI_ReceiveData(void);

/* Assign each received value to the receiveData[] array */
void SPI_AssignNewData();

#endif