#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"

GPIO_InitTypeDef gpioPC13;
void config();

int main (void) {

	config();
	while (1) {
		// Blink LED on PC13
		Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
		delayMs(100);
    Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
		delayMs(100);
		Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
		delayMs(100);
    Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
		delayMs(700);
		Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
		delayMs(100);
    Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
		delayMs(100);
		Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
		delayMs(100);
    Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
		delayMs(100);
		Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
		delayMs(100);
    Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
		delayMs(100);
		Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
		delayMs(100);
		Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
		delayMs(500);
	}
}

void config () {
	
	// Initialize TIM2
  TIM2_INT_Init();
	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioPC13.GPIO_Pin = GPIO_Pin_13;
	gpioPC13.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioPC13.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpioPC13);
	
}