/*
* File: uartMCU2.c
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file writes functions to initialize, transmit and 
* receive data according to the uart method
*/

#include "stm32f10x.h"
#include "uartMCU2.h"

/*
* Function: USART1_Init
* Description: Initialize uart1
* Input:
*   None
* Output:
*   None
*/
void USART1_Init (void) {
    /* Turn on clock for USART1, GIPIA and GPIOC */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

    /* Initialize GPIO */
    GPIO_InitTypeDef GPIO_InitStruct;
	
	  /* Pin Tx */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
	  /* Pin Rx */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	  /* Pin PC13 to check */
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* config USART1 */
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
		/* If the data word length is 8 (from 0 to 7) bits, the even bit is the 7th bit */
    USART_InitStruct.USART_Parity = USART_Parity_Even;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStruct);

    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);
}

/*
* Function: USART1_Send
* Description: Transmit data
* Input:
*   dataTransmit: data to Transmit
* Output:
*   None
*/
void USART1_Send (uint8_t dataTransmit) {
    
	  /* Wait for USART is ready to transfer data.  */ 
    while (!(USART1->SR & USART_SR_TXE));
  
    /* Transmit data */
  	USART1->DR = dataTransmit;
	
	  /* Wait for the data transmission to complete */
	  while (!(USART1->SR & USART_SR_TC ));
	  
	  /* Read value from Data Register (DR) to clear transmitted data. */
	  volatile uint8_t clear = USART1->DR;
}

/*
* Function: USART1_Receive
* Description: Receive data
* Input:
*   None
* Output:
*   None
*/
uint8_t USART1_Receive (void) {
	
    /* Wait for data to be received in USART1 */
    while (!(USART1->SR & USART_SR_RXNE));
    
	  /* Read data */
	  uint8_t checkParity = USART1->DR;
	
	  /* Check the parity of received data */
	  if (!isEvenParity(checkParity)) return 0;
	
    return checkParity;
	
}

/*
* Function: USART1_Receive_Transmit
* Description: Receive data from MCU1 and transmit back to MCU1 new data
* Input:
*   None
* Output:
*   None
*/
void USART1_Receive_Transmit () {

  uint8_t dataReceive =  USART1_Receive();
	
	/*
	* The selected mode is even bit check, so the 8th bit is the check bit, 
	* the maximum data value received is 127 corresponding to 1111111 (7 bits 1)
  */
	dataReceive = dataReceive & 127;
	dataReceive++;
	
	USART1_Send(dataReceive);

}

/*
* Function: isEvenParity
* Description: Check parity
* Input:
*   checkParity: Data needed to check parity
* Output:
*   None
*/
uint8_t isEvenParity (uint8_t checkParity) {
  
	/* count bit 1 */
	int count = 0;
  for (int i = 0; i < 8; i++) {
    if ((checkParity >> i) & 1) count++;        
  }
  return (count % 2) == 0;
	
}