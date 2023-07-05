/*
* File: spiTransmit.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file is created to write SPI constructors and transfer data
*/

#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "spiTransmit.h"

/*
* Function: SPI_Configuration
* Description: SPI initialization
* Input:
*   None
* Output:
*   None
*/
void SPI_Configuration (void) {
	
	/* Init GPIO */
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Init SPI */
	SPI_InitTypeDef SPI_InitStructure;
	
  /* Turn on clock for GPIO and SPI */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

  /* Config pin of SPI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; // SCK, MOSI
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Ch? d? Alternate Function Push-Pull
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Config for SPI */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  SPI_Cmd(SPI1, ENABLE);
	
}


/*
* Function: SPI_SendData
* Description: Data transmission
* Input:
*   data: Data to be transmitted
* Output:
*   None
*/
void SPI_SendData (uint8_t data) {

	/* Waits for SPI to be empty and ready to receive new data */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  /* Carrying out data transmission */
	SPI_I2S_SendData(SPI1, data);
	
	/* Wais for SPI is completed and SPI is no longer busy */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

}


