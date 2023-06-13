#include "stm32f10x.h"
#include "Dio.h"
#include "Multitasks.h"
#include "blinkLed.h"

GPIO_InitTypeDef gpioPC13;

int main (void) {

	config();
	TIM2_INT_Init();
	Task task1 = {&ledPC13, 600};
	Task task2 = {&ledPC13, 100};
	
	while (1) {
    multitasks(&task1);
		multitasks(&task2);
	}
}


void config () {

	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioPC13.GPIO_Pin = GPIO_Pin_13;
	gpioPC13.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioPC13.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpioPC13);
	
}
