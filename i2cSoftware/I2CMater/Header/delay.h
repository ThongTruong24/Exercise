/*
* File: delay.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: This is the file used to delay the time in millis and test the button 1 and 2
*/

#ifndef _DELAY_H
#define _DELAY_H

#include "stm32f10x.h"

/* Init TIM2 */
void TIM2_INT_Init();

/* Delay and test push button 1, 2 and 3 */
void delayMs(uint32_t ms);

#endif