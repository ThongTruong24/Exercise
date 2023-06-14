/*
* File: Dio.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This is the file used to declare functions written according to the autosar standard
*/

#ifndef _DIO_H
#define _DIO_H

#include "stm32f10x.h"

/* Declare an enum consisting of pin numbers */
typedef enum {
  DIO_CHANNEL_PA0,
	DIO_CHANNEL_PA1,
	DIO_CHANNEL_PA2,
	DIO_CHANNEL_PA3,
	DIO_CHANNEL_PA4,
	DIO_CHANNEL_PA5,
	DIO_CHANNEL_PA6,
	DIO_CHANNEL_PA7,
	DIO_CHANNEL_PA8,
	DIO_CHANNEL_PA9,
	DIO_CHANNEL_PA10,
	DIO_CHANNEL_PA11,
	DIO_CHANNEL_PA12,
	DIO_CHANNEL_PA13,
	DIO_CHANNEL_PA14,
	DIO_CHANNEL_PA15,
	
	DIO_CHANNEL_PB0,
	DIO_CHANNEL_PB1,
	DIO_CHANNEL_PB2,
	DIO_CHANNEL_PB3,
	DIO_CHANNEL_PB4,
	DIO_CHANNEL_PB5,
	DIO_CHANNEL_PB6,
	DIO_CHANNEL_PB7,
	DIO_CHANNEL_PB8,
	DIO_CHANNEL_PB9,
	DIO_CHANNEL_PB10,
	DIO_CHANNEL_PB11,
	DIO_CHANNEL_PB12,
	DIO_CHANNEL_PB13,
	DIO_CHANNEL_PB14,
	DIO_CHANNEL_PB15,
	
	DIO_CHANNEL_PC13,
 	DIO_CHANNEL_PC14,
	DIO_CHANNEL_PC15,
} Dio_ChannelType;

/* Declare an enum consisting of value status */
typedef enum {
  STD_LOW,
  STD_HIGH
} Dio_LevelType;

/* Service to set a level of a channel */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/* Returns the value of the specified DIO channel */
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);

/* Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return */
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId);

#endif