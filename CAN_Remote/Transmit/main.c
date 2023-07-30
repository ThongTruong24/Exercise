/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file is created to send request and receive data from node (pressure)
*/

#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
#include "LCD.h"

/*
* Function: init_can
* Description: Configuration communication CAN
* Input:
*   can_id: ID of NODE
* Ouput: 
*   None
*/
void init_can(uint16_t can_id){
	
	/* Declare configuration variables for GPIO and CAN */
  GPIO_InitTypeDef            GPIO_InitStructure;
  CAN_InitTypeDef             CAN_InitStructure;
  CAN_FilterInitTypeDef       CAN_FilterInitStructure;

	/* Enable clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* Config pin for CAN1 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Pin check */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
  CAN_InitStructure.CAN_TTCM = DISABLE;
	
	/*
  *	Automatic Bus-Off Management (ABOM): When enable CAN module will automatically handle the "Bus-Off" 
	* and to restore itself to resume normal operation without software
	*/
  CAN_InitStructure.CAN_ABOM = DISABLE;
	
  /* 
	* Automatic Wakeup Mode (AWUM): When enable it will enable to automatically "wakeup" the CAN module 
	* when a "wake-up" event occurs on the CAN bus. CAN module consumes very little power
	*/
  CAN_InitStructure.CAN_AWUM = DISABLE;
	
	/* 
	* No Automatic Retransmission (NART): When enable CAN module will not automatically try to resend the message 
	* if sending is unsuccessful, and immediately return an error status to the CAN control software
	*/
  CAN_InitStructure.CAN_NART = DISABLE;
	
	/* 
	* Receive FIFO Locked Mode (RFLM): When enable it will put the state of the receive FIFO (Receive FIFO) into "locked" mode (locked) 
	* after it is read by the software. 
  * This means that when a message is read from the receiving FIFO, it will not be deleted from the FIFO but no 
  * new messages can be received until it is released (unlocked) by the software
	*/
  CAN_InitStructure.CAN_RFLM = DISABLE;
	
	/* 
	* Transmit FIFO Priority (TXFP) : When enable messages in transmitters will be sent in priority order based on their priority
	*/
  CAN_InitStructure.CAN_TXFP = DISABLE;
	
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;





  /* 
	* Synchronization Jump Width (SJW): The minimum amount of time the CAN bus must be idle (no communication) before a new data 
	* transmission cycle begins
	*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	
	/* 
	* Bit Segment 1 (BS1) : The CAN signal propagates and passes through the signal management signal to all nodes in the network.
	*/
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
	
	/* 
	* Bit Segment 2 (BS2) : It determines the time from when the data signal ends until the CAN bus returns to the "wait" state 
	* to receive the next data bit.
	*/
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
	
	/*
  *	Determines the frequency (baud rate) of CAN communication
	* This frequency determines the communication speed between nodes in the network 
	* Recipe: 1 time quantum = 1/(system clock/4)
	*/
  CAN_InitStructure.CAN_Prescaler = 4;
  CAN_Init(CAN1, &CAN_InitStructure);





  /* Used to specify the filter sequence number configured for the CAN module */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
	
	/*
	* Used to determine which bits in the ID address should be compared 
	* and which bits should be ignored during filtering
	*/
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	
	/*
	* configure the 16 high bits of the ID address for the filter 
	* in the CAN module when using the "Identifier Mask Mode" filter mode
	*/
  CAN_FilterInitStructure.CAN_FilterIdHigh = can_id;
	/* 16 low bits */
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	
	/*
	* The mask is used to determine (& bit) which bits in the ID address need to be compared
	* and which bits should be ignored during filtering
	*/
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	
	/* Configure which FIFO filter to assign in the CAN module*/
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
}

/*
* Function: Request_Data_Pressure
* Description: Transmit message to NODEx (request data);
* Input:
*   id: ID of NODEx to transmit message
* Ouput: 
*   Transmit message to NODEx
*/
void Request_Data_Pressure (uint32_t id) {
	
  CanTxMsg TxMessage;
  TxMessage.StdId = id;
  TxMessage.ExtId = 0x00;
	
	/* Define message type: remote frame */
  TxMessage.RTR = CAN_RTR_REMOTE;
	
	/* CAN Identifier Standard */
  TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 0;
	
  CAN_Transmit(CAN1, &TxMessage);
	
	/* Wait until the current message frame is successfully transmitted */
  while (CAN_TransmitStatus(CAN1, CAN_FIFO0) != CAN_TxStatus_Ok);
		
}

/*
* Function: receive_Can_Message
* Description: Receive array of data from NODEx
* Input:
*   data: Data array received from NODEx
* Ouput: 
*   None
*/
void receive_Can_Message (uint8_t *data) {
    
  CanRxMsg RxMessage;
	
	/* Wait until a message arrives and wait to be processed in FIFO 0 */
  while (CAN_MessagePending(CAN1, CAN_FIFO0) == 0);

  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

  for (int i = 0; i < RxMessage.DLC; i++) data[i] = RxMessage.Data[i];
	
}

int main(){
	  
	init_can(0x0000);
  uint8_t data[3]= {0};
	
  Request_Data_Pressure(0x123);
	receive_Can_Message(data);
	
	/* Print data on LCD to check true or not */
  LCD_Init();
	LCD_SendString("Lish of pressure");
	LCD_SendCmd(0xC0);
	for (uint8_t i = 0; i < 3; i++) {
    LCD_PrintNumber(data[i]);
	  LCD_SendString(" ");
		
  }
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
}