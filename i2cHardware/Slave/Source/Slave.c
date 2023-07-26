/*
* File: Slave.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: write initialization and data transfer functions 
* in addition to i2c interface
*/

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "Slave.h"

/*
* Function: I2C1_Init
* Description: Initialize I2C1 for Slave
* Input:
*   None
* Output:
*   None
*/
void I2C1_Init(void) {
    
	/* Turn on clock for I2C1, GPIOB, and GPIOC */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    
	/* Initialize GPIO */
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/* Initialize I2C1 */
  I2C_InitTypeDef I2C_InitStruct;
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct.I2C_OwnAddress1 = 48 << 1;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStruct.I2C_ClockSpeed = 100000;
  I2C_Init(I2C1, &I2C_InitStruct);
   
	/* Enable I2C1 */
  I2C_Cmd(I2C1, ENABLE);
}

/*
* Function: I2C_CheckAckNack
* Description: Check for ACK/NACK received from the master
* Input:
*   None
* Output:
*   Returns 1 if NACK received, 0 if ACK received
*/
uint8_t I2C_CheckAckNack(void) {
  if (I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_ACK_FAILURE)) return 1;
	// ACK received
  else return 0; 
}

/*
* Function: I2C1_WaitForAddress
* Description: Wait for the slave address match and receiver mode
* Input:
*   None
* Output:
*   Returns the value of the SR1 register
*/
uint8_t I2C1_WaitForAddress(void) {
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED));
  return I2C1->SR1;
}

/*
* Function: I2C_Receiver
* Description: Receive data from the I2C bus
* Input:
*   receivedData: Pointer to the data buffer to store received data
*   length: Number of bytes to receive
* Output:
*   None
*/
void I2C_Receiver (uint8_t *receivedData, uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_BYTE_RECEIVED));
    receivedData[i] = I2C_ReceiveData(I2C1);
  }
}

/*
* Function: I2C_Transmitter
* Description: Transmit data to the I2C bus
* Input:
*   receivedData: Pointer to the data buffer to be transmitted
*   length: Number of bytes to transmit
* Output:
*   None
*/
void I2C_Transmitter (uint8_t *receivedData, uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    I2C_SendData(I2C1, receivedData[i]);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_BYTE_TRANSMITTED));
    if (I2C_CheckAckNack() == 1) return;
  }
}