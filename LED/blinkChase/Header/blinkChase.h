#ifndef _BLINKCHASE_H
#define _BLINKCHASE_H

#include "stm32f10x.h"

void butTon1();
void butTon2();
void butTon3();

void blinkLed(uint8_t dem);
void lightChaseLed(uint8_t dem);
void offLed();
void offLedAndCheck();

#endif