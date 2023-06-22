/*
* File: spiAutosar.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file is created to write spi functions according to the autosar standard
*/

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "spiAutosar.h"

/*
* Function: Spi_Init
* Description: Service for SPI initialization.
* Input:
*   ConfigPtr: Pointer to configuration set
* Output:
*   None
*/
void Spi_Init (Spi_ConfigType* ConfigPtr) {
	
	/* Initialize SPI */
	RCC_APB2PeriphClockCmd(SPIx_RCC, ENABLE);
	ConfigPtr->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	ConfigPtr->SPI_CPHA = SPI_CPHA_1Edge;
	ConfigPtr->SPI_CPOL = SPI_CPOL_Low;
  ConfigPtr->SPI_DataSize = SPI_DataSize_8b;
	ConfigPtr->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	ConfigPtr->SPI_FirstBit = SPI_FirstBit_MSB;
	ConfigPtr->SPI_Mode = SPI_Mode_Master;
	ConfigPtr->SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_Init(SPIx, ConfigPtr); 
	SPI_Cmd(SPIx, ENABLE);
	
}

/*
* Function: Spi_WriteIB
* Description: Service for writing one or more data to an IB SPI Handler/Driver Channel specified
*by parameter.
* Input:
*   Channel: Channel ID.
*   DataBufferPtr: Pointer to source data buffer. If this pointer is null, it is assumed that
*                  the data to be transmitted is not relevant and the default transmit
*                  value of this channel will be used instead. 
* Output:
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPtr) {

	switch (Channel) {
	
		case SPI_CHANNEL_1:
			
	    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
	    /* GPIO pins for MOSI, MISO, and SCK */
		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		  /* GPIO pin for SS */
		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		
		  /* Check if DataBufferPtr poiter is NULL */
		  if (DataBufferPtr == 0) return E_NOT_OK;
		    
		    /* Condition trasmit all data */
     	while (DataBufferPtr != 0) {
			    
				/* Wait until transmit buffer is empty */
			  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
					
				/* Send data to SPI data register */ 
        SPI_I2S_SendData(SPIx, DataBufferPtr->value);
					
				/* Wait until SPI is not busy anymore */
        while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);
					
				/* Assign pointer to next data */
			  DataBufferPtr = DataBufferPtr->node;
			}
			break;
		
		case SPI_CHANNEL_2:

	    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);

		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

		  if (DataBufferPtr == 0) return E_NOT_OK;
		    
      while (DataBufferPtr != 0) {
			    
			  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPIx, DataBufferPtr->value);
        while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);

			  DataBufferPtr = DataBufferPtr->node;
		  }
		  break;
				
		case SPI_CHANNEL_3:
			
	    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		  
		  if (DataBufferPtr == 0) return E_NOT_OK;
		    
      while (DataBufferPtr != 0) {
			    
			  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPIx, DataBufferPtr->value);
        while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);

			  DataBufferPtr = DataBufferPtr->node;
		  }
		  break;
		
		case SPI_CHANNEL_INVALID:
		  return E_NOT_OK;
	
	}
}

/*
* Function: Spi_ReadIB
* Description: Service for reading synchronously one or more data from an IB SPI 
*Handler/Driver Channel specified by parameter.
* Input:
*   Channel: Channel ID.
* Output:
*   DataBufferPointer: Pointer to destination data buffer in RAM
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer) {

  	switch (Channel) {
	
		case SPI_CHANNEL_1:
			
	    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
	    /* GPIO pins for MOSI, MISO, and SCK */
		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		  /* GPIO pin for SS */
		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		
		  /* Check if DataBufferPtr poiter is NULL */
		  if (DataBufferPointer == 0) return E_NOT_OK;
		  
	  	while (DataBufferPointer != 0) {
			
        /* Wait until SPI is ready to receive data */
			  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
					
				/* Assign the data to DataBufferPointer */
				DataBufferPointer->value = SPI_I2S_ReceiveData(SPIx);
				  
			  /* Assign pointer to next data */
			  DataBufferPointer = DataBufferPointer->node;
		  }
			break;
		
		case SPI_CHANNEL_2:
			
	    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);

		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		
		  if (DataBufferPointer == 0) return E_NOT_OK;
		  
	  	while (DataBufferPointer != 0) {
			
        while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
			  DataBufferPointer->value = SPI_I2S_ReceiveData(SPIx);
				
			  DataBufferPointer = DataBufferPointer->node;
		  }
			break;
				
		case SPI_CHANNEL_3:
			
	    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

		  GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		
		  if (DataBufferPointer == 0) return E_NOT_OK;
		  
	  	while (DataBufferPointer != 0) {
			
        while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
			  DataBufferPointer->value = SPI_I2S_ReceiveData(SPIx);
				
			  DataBufferPointer = DataBufferPointer->node;
		  }
			break;
			
		case SPI_CHANNEL_INVALID:
		  return E_NOT_OK;
	
	}
	
}

/*
* Function: Spi_DeInit
* Description: Service for SPI de-initialization.
* Input:
*   None
* Output:
*   E_OK: de-initialisation command has been accepted
*   E_NOT_OK: de-initialisation command has not been accepted
*/
Std_ReturnType Spi_DeInit () {

  if (SPI1->CR1 == 0 && GPIOA->CRL == 0) return E_OK;
  else return E_NOT_OK;
	
}


int main () {}

