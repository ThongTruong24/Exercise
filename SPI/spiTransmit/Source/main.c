#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "spiTransmit.h"

GPIO_InitTypeDef gpio;
void configOutput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void config();

int main() {

	config();
	TIM2_INT_Init();
	spiInit();
  delayMs(2000);
	
  uint8_t data = 162;
  while(1) {
	  transmit(data);
		delayMs(2000);
	}
}
	
	
void configOutput (uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx) {
  gpio.GPIO_Pin = GPIO_Pin;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOx, &gpio);
}

void config() {
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
  configOutput(GPIO_Pin_12, GPIOB);
  configOutput(GPIO_Pin_13, GPIOB);
  configOutput(GPIO_Pin_14, GPIOB);
	
}
