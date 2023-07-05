/*
* File: spiReceive.c
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This is the file used to write SPI constructors and transfer data
*/

#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "spiReceive.h"

/*
* Variable is defined in another source file and the current 
* file is accessing its declaration to use it
*/
extern uint8_t receiveData[4];

/*
* Function: SPI_Configuration
* Description: Config SPI
* Input:
*   None
* Output:
*   None
*/
void SPI_Configuration (void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStructure;
	
  /* Turn on clock fo GPIO and SPI */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOC, ENABLE);

  /* Config pin of SPI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Config for SPI */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
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
* Function: SPI_ReceiveData
* Description: Receive data
* Input:
*   None
* Output:
*   Return the received value
*/
uint8_t SPI_ReceiveData (void) {
  /* Wait for SPI to receive data */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Returns received data */
  return SPI_I2S_ReceiveData(SPI1);
}

/*
* Function: SPI_AssignNewData
* Description: Assign each received value to the receiveData[] array
* Input:
*   None
* Output:
*   None
*/
void SPI_AssignNewData() {

	for (int i = 0; i < 4; i++) {
		
		receiveData[i] = SPI_ReceiveData();
		
	}
}
