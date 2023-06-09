#include "stm32f10x.h"
#include "Dio.h"

GPIO_InitTypeDef gpio;
void configInput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void configOutput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void config();

void delay(uint32_t indexDelay);
void delayAndCheck();
void offLedAndCheck();

void butTon1();
void butTon2();
void butTon3();

void blinkLed(uint8_t dem);
void lightChaseLed(uint8_t dem);
void offLed();

int main() {
  config();
  while(1) {
	  butTon1();
	  butTon2();
  }
}
	
void configInput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx) {
  gpio.GPIO_Pin = GPIO_Pin;
  gpio.GPIO_Mode = GPIO_Mode_IPU;
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
	
void delay(uint32_t indexDelay) {
  uint32_t i;
  for(i = 0; i < indexDelay; i++){}
}
	
void delayAndCheck() {
  delay(500000);
  butTon1();
  butTon2();
  butTon3();
  delay(500000);
  butTon1();
  butTon2();
  butTon3();
}
	
void butTon1() {
  if (Dio_ReadChannel(DIO_CHANNEL_PB12) == STD_HIGH) {
    while(1) {
      if (Dio_ReadChannel(DIO_CHANNEL_PB12) != STD_HIGH) blinkLed(5);
    }
  }
}

void butTon2() {
  if (Dio_ReadChannel(DIO_CHANNEL_PB13) == STD_HIGH) {
	  while(1) {
		  if (Dio_ReadChannel(DIO_CHANNEL_PB13) != STD_HIGH) lightChaseLed(5);
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
	  delayAndCheck();
	  Dio_WriteChannel(DIO_CHANNEL_PB15, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA8, STD_HIGH);
    Dio_WriteChannel(DIO_CHANNEL_PA9, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA10, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PA12, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PB6, STD_HIGH);
	  Dio_WriteChannel(DIO_CHANNEL_PB7, STD_HIGH);
	  delayAndCheck();
		offLed();
		delayAndCheck();
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

void lightChaseLed(uint8_t dem) {
  int8_t i = 0;
  offLed();
  while(i < dem) {
    i++;
	  Dio_WriteChannel(DIO_CHANNEL_PB15, STD_HIGH);
		delayAndCheck();
		Dio_WriteChannel(DIO_CHANNEL_PB15, STD_LOW);
		Dio_WriteChannel(DIO_CHANNEL_PA8, STD_HIGH);
		delayAndCheck();
		Dio_WriteChannel(DIO_CHANNEL_PA8, STD_LOW);
		Dio_WriteChannel(DIO_CHANNEL_PA9, STD_HIGH);
	  delayAndCheck();
		Dio_WriteChannel(DIO_CHANNEL_PA9, STD_LOW);
	  Dio_WriteChannel(DIO_CHANNEL_PA10, STD_HIGH);
	  delayAndCheck();
		Dio_WriteChannel(DIO_CHANNEL_PA10, STD_LOW);
	  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_HIGH);
	  delayAndCheck();
	  Dio_WriteChannel(DIO_CHANNEL_PA11, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_PA12, STD_HIGH);
    delayAndCheck();
    Dio_WriteChannel(DIO_CHANNEL_PA12, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_PB6, STD_HIGH);
    delayAndCheck();
    Dio_WriteChannel(DIO_CHANNEL_PB6, STD_LOW);
    Dio_WriteChannel(DIO_CHANNEL_PB7, STD_HIGH);
    delayAndCheck();
  	Dio_WriteChannel(DIO_CHANNEL_PB7, STD_LOW);
    }
	  offLedAndCheck();
	}
	
void offLedAndCheck() {
  offLed();	
  while(1) {
		butTon1();
		butTon2();
	}
}