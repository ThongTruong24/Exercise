/*
* File: blinkChase.h 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Here is the file that does the led operations and checks the input buttons
*/

#ifndef _BLINKCHASE_H
#define _BLINKCHASE_H

#include "stm32f10x.h"

/* Check push button1 and execute led according to respective function */
void butTon1();
void butTon2();
void butTon3();

/* blinking leds */
void blinkLed(uint8_t dem);

/* Chasing the light of led */
void lightChaseLed(uint8_t dem);

/* Off all leds */
void offLed();

/* Off all leds and check button 1/2 */
void offLedAndCheck();

#endif