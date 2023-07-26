/*
* File: Master.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: File definition of functions in file Master.c
*/

#ifndef _MASTER_H
#define _MASTER_H

#include "stm32f10x.h"

/* Check if I2C device acknowledged or not */
void I2C1_Init(void);

/* Check if I2C device acknowledged or not */
void I2C_StartCondition(void);

/* Check if I2C device acknowledged or not */
void I2C1_ConditionStop(void);

/* Check if I2C device acknowledged or not */
uint8_t I2C_CheckAckNack(void);

/* Check if I2C device acknowledged or not */
void I2C_SendAddress(uint8_t deviceAddr, uint8_t direction);

/* Check if I2C device acknowledged or not */
void I2C_Transmitter (uint8_t address, uint8_t *data, uint8_t length);

/* Check if I2C device acknowledged or not */
void I2C_Receiver (uint8_t address,uint8_t *data, uint8_t length);

#endif