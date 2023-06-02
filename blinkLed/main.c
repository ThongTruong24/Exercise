#include "stm32f10x.h"
#include "Dio.h"

void config();
void delay(uint32_t indexDelay);

int main() {
	config();
	while(1) {
	  Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
	  delay(1000000);
    Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
	  delay(1000000);
	}
}
	
void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio);
}

void delay(uint32_t indexDelay){
	uint32_t i;
	for(i = 0; i < indexDelay; i++);
}