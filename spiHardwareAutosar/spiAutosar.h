/*
* File: spiAutosar.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description:  This file is created to define the functions and macros of 
*the spi interface according to the autosar standard
*/

#ifndef _SPIAUTOSAR_H
#define _SPIAUTOSAR_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

/* Define the pins, assuming we use spi1 on pins 4 5 6 and 7 of port A 
*According to autosar, these pins are already defined, 
*in this case we define them ourselves
*/
#define SPIx_RCC				RCC_APB2Periph_SPI1
#define SPIx						SPI1
#define SPI_GPIO_RCC		RCC_APB2Periph_GPIOA
#define SPI_GPIO				GPIOA
#define SPI_PIN_MOSI		GPIO_Pin_7
#define SPI_PIN_MISO		GPIO_Pin_6
#define SPI_PIN_SCK			GPIO_Pin_5
#define SPI_PIN_SS			GPIO_Pin_4

/* Defines two values for the return result of an action, 
*that is E_OK and E_NOT_OK. */
typedef enum {
	
  E_OK,
  E_NOT_OK
	
} Std_ReturnType;

/* Defines values for SPI channels and adds a special value 
* to indicate invalid channel. */
typedef enum {
	
    SPI_CHANNEL_1,
    SPI_CHANNEL_2,
    SPI_CHANNEL_3,
    SPI_CHANNEL_INVALID
	
} Spi_ChannelType;

#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1

/* Defines two members required for transmitting and receiving data in SPI */
typedef struct {
	
    uint8_t *node;
    uint32_t value;
	
} Spi_DataBufferType;

typedef SPI_InitTypeDef Spi_ConfigType;
GPIO_InitTypeDef GPIO_InitStruct;

/* Service for SPI initialization */
void Spi_Init (Spi_ConfigType* ConfigPtr);

/* Service for writing one or more data to an IB SPI Handler/Driver 
*Channel specified by parameter
*/
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPtr);

/* Service for reading synchronously one or more data from an IB SPI */
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer);

/* Service for SPI de-initialization */
Std_ReturnType Spi_DeInit ();

#endif