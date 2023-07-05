/*
* File: spiTransmit.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This is the file used to define constructors and transfer data
*/

#ifndef _SPITRANSMIT_H
#define _SPITRANSMIT_H

#include "stm32f10x.h"

/* SPI initialization */
void SPI_Configuration(void);

/* Data transmission */ 
void SPI_SendData(uint8_t data);

#endif