/*
* File: spiTransmit.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This is the file used to write functions that perform data transfer
*/

#ifndef _spiTransmit_H
#define _spiTransmit_H

#include "stm32f10x.h"

/* Set the transmitted clock signal */
void clock();

/* Set the initial state for the pins */
void spiInit();

/* Transmit data by setting the corresponding output levels of the SS, MOSI and SCK pins */
void transmit(uint8_t);

#endif
