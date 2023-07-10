/*
* File: uartMCU1.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file defines the functions in the file uartMCU1.c
*/

#ifndef _UARTMCU1_H
#define _UARTMCU1_H

#include "stm32f10x.h"

/* Init uart1 */
void USART1_Init(void);

/* Transmit data */
void USART1_Send(uint8_t dataTransmit);

/* Receive data */
uint8_t USART1_Receive(void);

/* Check parity */
uint8_t isEvenParity(uint8_t checkParity);

#endif