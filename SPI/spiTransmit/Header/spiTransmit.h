#ifndef _spiTransmit_H
#define _spiTransmit_H

#include "stm32f10x.h"

void clock();
void spiInit();
void transmit(uint8_t);

#endif
