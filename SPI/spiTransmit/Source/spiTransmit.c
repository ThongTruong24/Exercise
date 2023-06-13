#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "spiTransmit.h"

#define SCK DIO_CHANNEL_PB12
#define MOSI DIO_CHANNEL_PB13
#define SS DIO_CHANNEL_PB14

void spiInit () {
	
  Dio_WriteChannel(SCK, STD_LOW);
	Dio_WriteChannel(MOSI, STD_LOW);
  Dio_WriteChannel(SS, STD_HIGH);
	
}

void clock () {
	
  Dio_WriteChannel(SCK, STD_HIGH);
	delayMs(500);
	Dio_WriteChannel(SCK, STD_LOW);
	delayMs(500);
	
}

void transmit (uint8_t data) {
	
	Dio_WriteChannel(SS, STD_LOW);
  uint8_t i = 0;
	for ( ; i < 8; i++) {
		
	  if (data & (1 << (7 - i))) Dio_WriteChannel(MOSI, STD_HIGH);
		else Dio_WriteChannel(MOSI, STD_LOW);

		clock();
	}
	Dio_WriteChannel(SS, STD_HIGH);
	
}