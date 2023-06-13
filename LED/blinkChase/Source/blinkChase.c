#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "blinkChase.h"

void butTon1() {
	
  if (Dio_ReadChannel(DIO_CHANNEL_PB12) == STD_HIGH) {
		
    while(1) {
      if (Dio_ReadChannel(DIO_CHANNEL_PB12) != STD_HIGH) blinkLed(9);
    }
		
  }
}

void butTon2() {
	
  if (Dio_ReadChannel(DIO_CHANNEL_PB13) == STD_HIGH) {
		
	  while(1) {
		  if (Dio_ReadChannel(DIO_CHANNEL_PB13) != STD_HIGH) lightChaseLed(9);
		}
		
  }
}

void butTon3() {
	
  if (Dio_ReadChannel(DIO_CHANNEL_PB14) == STD_HIGH) offLedAndCheck();
	
}

void blinkLed(uint8_t dem) {
	
  uint8_t i = 0;
  while(i < dem) {
    i++;
	  Dio_WriteChannel(DIO_CHANNEL_PB15, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA8, STD_HIGH);
    Dio_WriteChannel(DIO_CHANNEL_PA9, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA10, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA12, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PB6, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PB7, STD_HIGH);
	  delayMs(100);
		offLed();
		delayMs(100);
  }
	offLedAndCheck();
	
}

void lightChaseLed(uint8_t dem) {
	
  int8_t i = 0;
  offLed();
  while(i < dem) {
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
	  offLedAndCheck();
		
}
	
void offLed() {
	
  Dio_WriteChannel(DIO_CHANNEL_PB15, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA8, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA9, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA10, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PA12, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PB6, STD_LOW);
  Dio_WriteChannel(DIO_CHANNEL_PB7, STD_LOW);
	
}

void offLedAndCheck() {
	
  offLed();	
  while(1) {
		butTon1();
		butTon2();
	}

}





	