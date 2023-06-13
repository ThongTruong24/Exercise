#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "blinkChase.h"

GPIO_InitTypeDef gpio;
void configInput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void configOutput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void config();

int main() {

  config();
	TIM2_INT_Init();
	
  while(1) {
	  butTon1();
	  butTon2();

  }
}
	
void configInput (uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx) {
	
  gpio.GPIO_Pin = GPIO_Pin;
  gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOx, &gpio);
	
} 
	
void configOutput (uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx) {
	
  gpio.GPIO_Pin = GPIO_Pin;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOx, &gpio);
	
}

void config() {
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
  configInput(GPIO_Pin_12, GPIOB);
  configInput(GPIO_Pin_13, GPIOB);
  configInput(GPIO_Pin_14, GPIOB);
		
  configOutput(GPIO_Pin_15, GPIOB);
  configOutput(GPIO_Pin_8, GPIOA);
  configOutput(GPIO_Pin_9, GPIOA);
  configOutput(GPIO_Pin_10, GPIOA);
  configOutput(GPIO_Pin_11, GPIOA);
  configOutput(GPIO_Pin_12, GPIOA);
  configOutput(GPIO_Pin_6, GPIOB);
  configOutput(GPIO_Pin_7, GPIOB);
	
}
	


