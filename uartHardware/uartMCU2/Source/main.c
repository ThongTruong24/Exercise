/*
* File: main.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Receive and transmit data form MCU1
*/

#include "stm32f10x.h"
#include "delay.h"
#include "LCD.h"
#include "uartMCU2.h"
#include "interrupt.h"

int main (void) {
    /* Init uart1 and time2 */
	  USART1_Init();
	  TIM2_INT_Init();

	  while(1) {
	}
}
