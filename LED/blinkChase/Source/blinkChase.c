/*
* File: blinkChase.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Write functions blink, chase led and function to check input buttons
*/

#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "blinkChase.h"

/*
* Function: butTon1
* Description: Check push button1 and execute led according to respective function
* Input:
*   None
* Output:
*   None
*/
void butTon1() {
	
	/* Check if button 1 is pressed or not */
  if (Dio_ReadChannel(DIO_CHANNEL_PB12) == STD_HIGH) {
		
    while(1) {
			
			/* Check the multiplier button is released */
      if (Dio_ReadChannel(DIO_CHANNEL_PB12) != STD_HIGH) blinkLed(9);
    }
		
  }
}

/*
* Function: butTon2
* Description: Check push button2 and execute led according to respective function
* Input:
*   None
* Output:
*   None
*/
void butTon2() {
	
	/* Check if button 2 is pressed or not */
  if (Dio_ReadChannel(DIO_CHANNEL_PB13) == STD_HIGH) {
		
		/* Check the multiplier button is released */
	  while(1) {
		  if (Dio_ReadChannel(DIO_CHANNEL_PB13) != STD_HIGH) lightChaseLed(9);
		}
		
  }
}

/*
* Function: butTon3
* Description: Check push button3 and execute led according to respective function
* Input:
*   None
* Output:
*   None
*/
void butTon3() {
	
	/* Check if button 3 is pressed or not */
  if (Dio_ReadChannel(DIO_CHANNEL_PB14) == STD_HIGH) offLedAndCheck();
	
}

/*
* Function: blinkLed
* Description: blinking leds
* Input:
*   dem: The number of times blink led is entered
* Output:
*   None
*/
void blinkLed(uint8_t dem) {
	
  uint8_t i = 0;
	
	/* Check the number of LED blinks */
  while(i < dem) {
    i++;
		
		/* set bit high */
	  Dio_WriteChannel(DIO_CHANNEL_PB15, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA8, STD_HIGH);
    Dio_WriteChannel(DIO_CHANNEL_PA9, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA10, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA12, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PB6, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PB7, STD_HIGH);
	  delayMs(100);
		/* set bit low */
		offLed();
		delayMs(100);
  }
	
	/* Turn off all leds and check push button 1 and 2 */
	offLedAndCheck();
	
}

/*
* Function: lightChaseLed
* Description: Chasing the light of led
* Input:
*   dem: The number of times blink led is entered
* Output:
*   None
*/
void lightChaseLed(uint8_t dem) {
	
  int8_t i = 0;
  offLed();
	
	/* Check the number of LED blinks */
  while(i < dem) {
		
		/* chasing the light of led */
    i++;
	  Dio_WriteChannel(DIO_CHANNEL_PB15, STD_HIGH);
		delayMs(30);
		Dio_WriteChannel(DIO_CHANNEL_PB15, STD_LOW);
		Dio_WriteChannel(DIO_CHANNEL_PA8, STD_HIGH);
		delayMs(30);
		Dio_WriteChannel(DIO_CHANNEL_PA8, STD_LOW);
		Dio_WriteChannel(DIO_CHANNEL_PA9, STD_HIGH);
	  delayMs(30);
		Dio_WriteChannel(DIO_CHANNEL_PA9, STD_LOW);
	  Dio_WriteChannel(DIO_CHANNEL_PA10, STD_HIGH);
	  delayMs(30);
		Dio_WriteChannel(DIO_CHANNEL_PA10, STD_LOW);
	  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_HIGH);
	  delayMs(30);
	  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_PA12, STD_HIGH);
    delayMs(30);
    Dio_WriteChannel(DIO_CHANNEL_PA12, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_PB6, STD_HIGH);
    delayMs(30);
    Dio_WriteChannel(DIO_CHANNEL_PB6, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_PB7, STD_HIGH);
    delayMs(30);
  	Dio_WriteChannel(DIO_CHANNEL_PB7, STD_LOW);
    }
	
		/* Turn off all leds and check push button 1 and 2 */
	  offLedAndCheck();
		
}
	

/*
* Function: offLed
* Description: Off all leds
* Input:
*   None
* Output:
*   None
*/
void offLed() {
	
  /* Off all leds */
	Dio_WriteChannel(DIO_CHANNEL_PB15, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA8, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA9, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA10, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA12, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PB6, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PB7, STD_LOW);
	
}

/*
* Function: offLedAndCheck
* Description: Off all leds and check button 1/2
* Input:
*   None
* Output:
*   None
*/
void offLedAndCheck() {
	
  offLed();	
	
	/* Checking status of button */
  while(1) {
		butTon1();
		butTon2();
	}

}