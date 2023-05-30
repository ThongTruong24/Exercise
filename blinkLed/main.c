#include "stm32f10x.h"                  // Device header

void config();

void delay();
void delayCheck();
	
void butTon1();
void butTon2();
void butTon3();

void nhapNhay();
void sangDuoi();

void tat();
void tatCheck();

int main()
	{
		config();
    while(1)
			{
				butTon1();
				butTon2();
      }
	}
	
void config()
	{

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

		GPIO_InitTypeDef LED;
		
		// button 1
		LED.GPIO_Pin = GPIO_Pin_12;
		LED.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOB, &LED);
		
		// button 2
		LED.GPIO_Pin = GPIO_Pin_13;
		LED.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOB, &LED);
		
		// button 3
		LED.GPIO_Pin = GPIO_Pin_14;
		LED.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOB, &LED);
		
		// den 1
		LED.GPIO_Pin = GPIO_Pin_15;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &LED);
		
		//den 2
		LED.GPIO_Pin = GPIO_Pin_8;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &LED);
		
		//den 3
		LED.GPIO_Pin = GPIO_Pin_9;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &LED);
		
		//den 4
		LED.GPIO_Pin = GPIO_Pin_10;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &LED);
	
		//den 5
		LED.GPIO_Pin = GPIO_Pin_11;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &LED);
		
		//den 6
		LED.GPIO_Pin = GPIO_Pin_12;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &LED);
		
		//den 7
		LED.GPIO_Pin = GPIO_Pin_6;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &LED);
		
		//den 8
		LED.GPIO_Pin = GPIO_Pin_7;
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &LED);	
	}
	
void delay(uint32_t indexDelay)
	{
	uint32_t i;
	for(i = 0; i < indexDelay; i++){}
	}
	
void delayCheck()
	{
	  delay(500000);
		butTon1();
		butTon2();
		butTon3();
		delay(500000);
		butTon1();
		butTon2();
		butTon3();
	}
	
void butTon1()
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0) {
		  while(1)
		    {
			    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) != 0)
				  	{
				  		nhapNhay(5);
				  	}
		    }
		}
	}

void butTon2()
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0) {
			while(1)
				{
				  if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) != 0)
						{
							sangDuoi(5);
						}
		    }
		}
	}	

void butTon3()
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
      tatCheck();
		}
	}	


void nhapNhay(uint8_t dem)
	{
		uint8_t i = 0;
    while(i < dem)
			{
					i++;
			  	delayCheck();
				  GPIO_SetBits(GPIOB, GPIO_Pin_15);
					GPIO_SetBits(GPIOA, GPIO_Pin_8);
					GPIO_SetBits(GPIOA, GPIO_Pin_9);
					GPIO_SetBits(GPIOA, GPIO_Pin_10);
					GPIO_SetBits(GPIOA, GPIO_Pin_11);
					GPIO_SetBits(GPIOA, GPIO_Pin_12);
					GPIO_SetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
				  delayCheck();
			
					GPIO_ResetBits(GPIOB, GPIO_Pin_15);
					GPIO_ResetBits(GPIOA, GPIO_Pin_8);
					GPIO_ResetBits(GPIOA, GPIO_Pin_9);
					GPIO_ResetBits(GPIOA, GPIO_Pin_10);
					GPIO_ResetBits(GPIOA, GPIO_Pin_11);
					GPIO_ResetBits(GPIOA, GPIO_Pin_12);
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					delayCheck();
        }
		 tatCheck();
	}
	
void tat()
	{
	  	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
			GPIO_ResetBits(GPIOA, GPIO_Pin_9);
			GPIO_ResetBits(GPIOA, GPIO_Pin_10);
			GPIO_ResetBits(GPIOA, GPIO_Pin_11);
			GPIO_ResetBits(GPIOA, GPIO_Pin_12);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	}

void sangDuoi(uint8_t dem)
	{

		uint8_t i = 0;
		tat();
    while(i < dem)
			{
					i++;
				  delayCheck();
				  GPIO_SetBits(GPIOB, GPIO_Pin_15);
				  delayCheck();
				  GPIO_ResetBits(GPIOB, GPIO_Pin_15);
					GPIO_SetBits(GPIOA, GPIO_Pin_8);
				  delayCheck();
				  GPIO_ResetBits(GPIOA, GPIO_Pin_8);
					GPIO_SetBits(GPIOA, GPIO_Pin_9);
				  delayCheck();
				  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
					GPIO_SetBits(GPIOA, GPIO_Pin_10);
				  delayCheck();
				  GPIO_ResetBits(GPIOA, GPIO_Pin_10);
					GPIO_SetBits(GPIOA, GPIO_Pin_11);
			    delayCheck();
			   	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
					GPIO_SetBits(GPIOA, GPIO_Pin_12);
		  		delayCheck();
				  GPIO_ResetBits(GPIOA, GPIO_Pin_12);
					GPIO_SetBits(GPIOB, GPIO_Pin_6);
				  delayCheck();
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
				  delayCheck();
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
        }
		tatCheck();
	}
	
void tatCheck()
	{
		tat();	
		while(1)
				{
					butTon1();
					butTon2();
				}
	}