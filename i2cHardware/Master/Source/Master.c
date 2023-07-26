/*
* File: Master.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: write initialization and data transfer functions 
* in addition to i2c interface
*/

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "Master.h"

/*
* Function: I2C1_Init
* Description: Initialize I2C1 for Master
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
  I2C_InitStruct.I2C_OwnAddress1 = 0x00;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStruct.I2C_ClockSpeed = 100000;
  I2C_Init(I2C1, &I2C_InitStruct);

  /* Enable I2C1 */
  I2C_Cmd(I2C1, ENABLE);
}

/*
* Function: I2C_StartCondition
* Description: Generate I2C start condition
* Input:
*   None
* Output:
*   None
*/
void I2C_StartCondition(void) {
  I2C_GenerateSTART(I2C1, ENABLE);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
}

/*
* Function: I2C1_ConditionStop
* Description: Generate I2C stop condition
* Input:
*   None
* Output:
*   None
*/
void I2C1_ConditionStop(void) {
  I2C_GenerateSTOP(I2C1, ENABLE);
  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}

/*
* Function: I2C_CheckAckNack
* Description: Check if I2C device acknowledged or not
* Input:
*   None
* Output:
*   1 if not acknowledged (NACK), 0 if acknowledged (ACK)
*/
uint8_t I2C_CheckAckNack(void) {
  if (I2C_GetFlagStatus(I2C1, I2C_FLAG_AF) == SET) return 1;
  else return 0;
}

/*
* Function: I2C_SendAddress
* Description: Send address to I2C device
* Input:
*   deviceAddr: 7-bit address of the target device
*   direction: 0 for write, 1 for read
* Output:
*   None
*/
void I2C_SendAddress(uint8_t deviceAddr, uint8_t direction) {
  I2C_Send7bitAddress(I2C1, deviceAddr << 1, direction);
  if (direction == 0) while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  else while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
}

/*
* Function: I2C_Transmitter
* Description: Transmit data over I2C
* Input:
*   address: 7-bit address of the target device
*   data: pointer to the data buffer to be transmitted
*   length: number of bytes to be transmitted
* Output:
*   None
*/
void I2C_Transmitter(uint8_t address, uint8_t *data, uint8_t length) {
  I2C_StartCondition();
  I2C_SendAddress(address, 0);
  if (I2C_CheckAckNack() == 1) I2C1_ConditionStop();

  for (uint8_t i = 0; i < length; i++) {
    I2C_SendData(I2C1, data[i]);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    if (I2C_CheckAckNack() == 1) I2C1_ConditionStop();
  }
  I2C1_ConditionStop();
}

/*
* Function: I2C_Receiver
* Description: Receive data over I2C
* Input:
*   address: 7-bit address of the target device
*   data: pointer to the buffer to store the received data
*   length: number of bytes to be received
* Output:
*   None
*/
void I2C_Receiver(uint8_t address, uint8_t *data, uint8_t length) {
  I2C_StartCondition();
  I2C_SendAddress(address, 1);
  if (I2C_CheckAckNack() == 1) I2C1_ConditionStop();

  for (uint8_t i = 0; i < length; i++) {
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    data[i] = I2C_ReceiveData(I2C1);
    if (I2C_CheckAckNack() == 1) I2C1_ConditionStop();
  }
  I2C1_ConditionStop();
}