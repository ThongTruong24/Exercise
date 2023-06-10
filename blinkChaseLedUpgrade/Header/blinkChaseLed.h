#ifndef _BLINKCHASELED_H
#define _BLINKCHASELED_H

#include "stm32f10x.h"

GPIO_InitTypeDef gpio;

void configInput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void configOutput(uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void config();

void butTon1();
void butTon2();
void butTon3();

void blinkLed(uint8_t dem);
void lightChaseLed(uint8_t dem);
void offLed();
void offLedAndCheck();


#endif