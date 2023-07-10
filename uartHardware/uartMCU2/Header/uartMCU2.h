/*
* File: uartMCU2.h
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file defines the functions written in uartMCU2.c
*/

#ifndef _UARTMCU2_H
#define _UARTMCU2_H

#include "stm32f10x.h"

/* Initialize uart1 */
void USART1_Init(void);

/* Transmit data */
void USART1_Send(uint8_t dataTransmit);

/* Receive data */
uint8_t USART1_Receive(void);

/* Receive data from MCU1 and transmit back to MCU1 new data */
void USART1_Receive_Transmit();

/* Check parity */
uint8_t isEvenParity(uint8_t checkParity);

#endif