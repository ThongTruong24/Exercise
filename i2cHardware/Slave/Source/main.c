/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Slave program receives data from Master 
* and then sends new data back 
*/

#include "stm32f10x.h"
#include "LCD.h"
#include "delay.h"
#include "Slave.h"

int main() {
  uint8_t receivedData[5] = {0};
  I2C1_Init();

  while(1) {
    uint8_t checkWorR = I2C1_WaitForAddress();
    if (I2C_CheckAckNack() == 1) return 0;

    if (checkWorR == 0) I2C_Receiver(receivedData, 5);
    else I2C_Transmitter(receivedData, 5);

    receivedData[2] = 2;
  }
}