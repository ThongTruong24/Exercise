/*
* File: Dio.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Declare functions written according to the autosar standard
*/

#include "Dio.h"

/*
* Function: Dio_FlipChannel
* Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return
* the level of the channel after flip.
* Input:
*   ChannelId: ID of DIO channel
* Output:
*   Dio_LevelType: 
*     STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
*     STD_LOW: The physical level of the corresponding Pin isSTD_LOW.
*/
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId) {
	
  GPIO_TypeDef* gpioPort;
  uint16_t gpioPin;
  switch (ChannelId) {
    case DIO_CHANNEL_PA0:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_0;
      break;
    case DIO_CHANNEL_PA1:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_1;
      break;
    case DIO_CHANNEL_PA2:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_2;
      break;
    case DIO_CHANNEL_PA3:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_3;
      break;
    case DIO_CHANNEL_PA4:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_4;
      break;
    case DIO_CHANNEL_PA5:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_5;
      break;
    case DIO_CHANNEL_PA6:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_6;
      break;
    case DIO_CHANNEL_PA7:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_7;
      break;
    case DIO_CHANNEL_PA8:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_8;
      break;
    case DIO_CHANNEL_PA9:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_9;
      break;
    case DIO_CHANNEL_PA10:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_10;
      break;
    case DIO_CHANNEL_PA11:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_11;
      break;
    case DIO_CHANNEL_PA12:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_12;
      break;
    case DIO_CHANNEL_PA13:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PA14:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PA15:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_15;
      break;
    case DIO_CHANNEL_PB0:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_0;
      break;
    case DIO_CHANNEL_PB1:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_1;
    break;
    case DIO_CHANNEL_PB2:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_2;
      break;
    case DIO_CHANNEL_PB3:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_3;
      break;
    case DIO_CHANNEL_PB4:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_4;
      break;
    case DIO_CHANNEL_PB5:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_5;
      break;
    case DIO_CHANNEL_PB6:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_6;
      break;
    case DIO_CHANNEL_PB7:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_7;
      break;
    case DIO_CHANNEL_PB8:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_8;
      break;
    case DIO_CHANNEL_PB9:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_9;
      break;
    case DIO_CHANNEL_PB10:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_10;
     break;
    case DIO_CHANNEL_PB11:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_11;
      break;
    case DIO_CHANNEL_PB12:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_12;
      break;
    case DIO_CHANNEL_PB13:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PB14:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PB15:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_15;
      break;
    case DIO_CHANNEL_PC13:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PC14:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PC15:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_15;
      break;
	}
	gpioPort->ODR ^= gpioPin;
}

/*
* Function: Dio_WriteChannel
* Description: Service to set a level of a channel
* the level of the channel after flip.
* Input:
*   ChannelId: ID of DIO channel
*   Level: Value to be written
* Output:
*   None
*/
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level) {
	GPIO_TypeDef* gpioPort;
  uint16_t gpioPin;
  switch (ChannelId) {
    case DIO_CHANNEL_PA0:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_0;
      break;
    case DIO_CHANNEL_PA1:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_1;
      break;
    case DIO_CHANNEL_PA2:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_2;
      break;
    case DIO_CHANNEL_PA3:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_3;
      break;
    case DIO_CHANNEL_PA4:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_4;
      break;
    case DIO_CHANNEL_PA5:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_5;
      break;
    case DIO_CHANNEL_PA6:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_6;
      break;
    case DIO_CHANNEL_PA7:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_7;
      break;
    case DIO_CHANNEL_PA8:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_8;
      break;
    case DIO_CHANNEL_PA9:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_9;
      break;
    case DIO_CHANNEL_PA10:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_10;
      break;
    case DIO_CHANNEL_PA11:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_11;
      break;
    case DIO_CHANNEL_PA12:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_12;
      break;
    case DIO_CHANNEL_PA13:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PA14:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PA15:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_15;
      break;
    case DIO_CHANNEL_PB0:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_0;
      break;
    case DIO_CHANNEL_PB1:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_1;
    break;
    case DIO_CHANNEL_PB2:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_2;
      break;
    case DIO_CHANNEL_PB3:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_3;
      break;
    case DIO_CHANNEL_PB4:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_4;
      break;
    case DIO_CHANNEL_PB5:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_5;
      break;
    case DIO_CHANNEL_PB6:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_6;
      break;
    case DIO_CHANNEL_PB7:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_7;
      break;
    case DIO_CHANNEL_PB8:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_8;
      break;
    case DIO_CHANNEL_PB9:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_9;
      break;
    case DIO_CHANNEL_PB10:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_10;
     break;
    case DIO_CHANNEL_PB11:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_11;
      break;
    case DIO_CHANNEL_PB12:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_12;
      break;
    case DIO_CHANNEL_PB13:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PB14:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PB15:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_15;
      break;
    case DIO_CHANNEL_PC13:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PC14:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PC15:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_15;
      break;		
	}
	if (Level == STD_LOW) GPIO_ResetBits(gpioPort, gpioPin);
	else GPIO_SetBits(gpioPort, gpioPin);		
}

/*
* Function: Dio_ReadChannel
* Description: Returns the value of the specified DIO channel.
* the level of the channel after flip.
* Input:
*   ChannelId: ID of DIO channel
* Output:
*   Dio_LevelType: 
*     STD_HIGH The physical level of the corresponding Pin is STD_HIGH
*     STD_LOW The physical level of the corresponding Pin is STD_LOW
*/
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId) {
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	switch(ChannelId) {
		case DIO_CHANNEL_PA0:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_0;
      break;
    case DIO_CHANNEL_PA1:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_1;
      break;
    case DIO_CHANNEL_PA2:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_2;
      break;
    case DIO_CHANNEL_PA3:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_3;
      break;
    case DIO_CHANNEL_PA4:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_4;
      break;
    case DIO_CHANNEL_PA5:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_5;
      break;
    case DIO_CHANNEL_PA6:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_6;
      break;
    case DIO_CHANNEL_PA7:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_7;
      break;
    case DIO_CHANNEL_PA8:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_8;
      break;
    case DIO_CHANNEL_PA9:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_9;
      break;
    case DIO_CHANNEL_PA10:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_10;
      break;
    case DIO_CHANNEL_PA11:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_11;
      break;
    case DIO_CHANNEL_PA12:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_12;
      break;
    case DIO_CHANNEL_PA13:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PA14:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PA15:
      gpioPort = GPIOA;
      gpioPin  = GPIO_Pin_15;
      break;
    case DIO_CHANNEL_PB0:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_0;
      break;
    case DIO_CHANNEL_PB1:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_1;
    break;
    case DIO_CHANNEL_PB2:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_2;
      break;
    case DIO_CHANNEL_PB3:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_3;
      break;
    case DIO_CHANNEL_PB4:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_4;
      break;
    case DIO_CHANNEL_PB5:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_5;
      break;
    case DIO_CHANNEL_PB6:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_6;
      break;
    case DIO_CHANNEL_PB7:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_7;
      break;
    case DIO_CHANNEL_PB8:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_8;
      break;
    case DIO_CHANNEL_PB9:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_9;
      break;
    case DIO_CHANNEL_PB10:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_10;
     break;
    case DIO_CHANNEL_PB11:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_11;
      break;
    case DIO_CHANNEL_PB12:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_12;
      break;
    case DIO_CHANNEL_PB13:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PB14:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PB15:
      gpioPort = GPIOB;
      gpioPin  = GPIO_Pin_15;
      break;
    case DIO_CHANNEL_PC13:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_13;
      break;
    case DIO_CHANNEL_PC14:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_14;
      break;
    case DIO_CHANNEL_PC15:
      gpioPort = GPIOC;
      gpioPin  = GPIO_Pin_15;
      break;
	}
  if(GPIO_ReadInputDataBit(gpioPort, gpioPin) == 0) return STD_HIGH;
	else return STD_LOW;		
}