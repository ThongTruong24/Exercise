/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This file is created to transmit array of data by communication can
*/

#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

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
* Function: send_Can_Message
* Description: Transmit array of data to NODEx
* Input:
*   id: Needed ID of NODEx to transmit
*   data: Array of data sent
*   len: Length of array
* Ouput: 
*   Transmit data to NODEx
*/
void send_Can_Message(uint32_t id, uint8_t *data, uint8_t len){
	
  CanTxMsg TxMessage;
  TxMessage.StdId = id;
  TxMessage.ExtId = 0x00;
	
	/* Define message type: data frame */
  TxMessage.RTR = CAN_RTR_DATA;
	
	/* CAN Identifier Standard */
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = len;

  for (int i = 0; i < len; i++) TxMessage.Data[i] = data[i];
   
  CAN_Transmit(CAN1, &TxMessage);
	
	/* Wait until the current message frame is successfully transmitted */
  while (CAN_TransmitStatus(CAN1, CAN_FIFO0) != CAN_TxStatus_Ok);
		
}


int main(){
	  
	init_can(0x0000);
	
  uint8_t data1[3]= {24, 47, 28};
  uint8_t data2[3]= {5, 73, 59};
  
  send_Can_Message(0x123, data1, 3);
	send_Can_Message(0x456, data2, 3);

	GPIO_SetBits(GPIOC, GPIO_Pin_13);
		
}