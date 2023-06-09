/*
* File: LCD.c 
* Author: Truong Huynh Quang Thong
* Date: 02/01/2003
* Description: Write functions that connect to LCD
*/

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "LCD.h"

/*
* Function: LCD_Init
* Description: Initialize the LCD and register the corresponding pins
* Input:
*   None
* Output:
*   None
*/

void LCD_Init(void) {
    
	GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable GPIO clock for LCD pins and GPIO for check PC13 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure LCD pins as output */
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_Pin = LCD_RS_PIN | LCD_RW_PIN | LCD_E_PIN | LCD_D4_PIN |
                             LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;
  GPIO_Init(LCD_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
	
  /* Initialization sequence */
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_RS_PIN);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_RW_PIN);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_E_PIN);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_D4_PIN);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_D5_PIN);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_D6_PIN);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_D7_PIN);

  /* Wait for LCD to power up */
  delayUs(15000);

  /* Function set: 4-bit mode, 2 lines, 5x8 font */
  LCD_SendCmd(0x28);
  delayUs(LCD_CMD_DELAY);

  /* Display control: display on, cursor off, blink off */
  LCD_SendCmd(0x0C);
  delayUs(LCD_CMD_DELAY);

  /* Clear display */
  LCD_SendCmd(0x01);
  delayUs(LCD_CMD_DELAY);

  /* Entry mode set: increment, no shift */
  LCD_SendCmd(0x06);
  delayUs(LCD_CMD_DELAY);
	
}

/*
* Function: LCD_SendCmd
* Description: Setting modes or profiles for LCD
* Input:
*   cmd: A numeric value or a predefined constant to represent a specific instruction
* Output:
*   None
*/
void LCD_SendCmd(uint8_t cmd) {
	
  /* Send higher nibble (4 bits) */
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_RS_PIN, Bit_RESET);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D4_PIN, (cmd >> 4) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D5_PIN, (cmd >> 5) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D6_PIN, (cmd >> 6) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D7_PIN, (cmd >> 7) & 0x01);
  GPIO_SetBits(LCD_GPIO_PORT, LCD_E_PIN);
  delayUs(LCD_DATA_DELAY);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_E_PIN);

  /* Send lower nibble (4 bits) */
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_RS_PIN, Bit_RESET);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D4_PIN, (cmd >> 0) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D5_PIN, (cmd >> 1) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D6_PIN, (cmd >> 2) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D7_PIN, (cmd >> 3) & 0x01);
  GPIO_SetBits(LCD_GPIO_PORT, LCD_E_PIN);
  delayUs(LCD_DATA_DELAY);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_E_PIN);
}

/*
* Function: LCD_SendData
* Description: Transmit data to LCD
* Input:
*   data: Data character is passed in
* Output:
*   Transmit the bits corresponding to the pins
*/
void LCD_SendData(uint8_t data) {
  
	/* Send higher nibble (4 bits) */
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_RS_PIN, Bit_SET);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D4_PIN, (data >> 4) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D5_PIN, (data >> 5) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D6_PIN, (data >> 6) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D7_PIN, (data >> 7) & 0x01);
  GPIO_SetBits(LCD_GPIO_PORT, LCD_E_PIN);
  delayUs(LCD_DATA_DELAY);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_E_PIN);

  /* Send lower nibble (4 bits) */
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_RS_PIN, Bit_SET);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D4_PIN, (data >> 0) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D5_PIN, (data >> 1) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D6_PIN, (data >> 2) & 0x01);
  GPIO_WriteBit(LCD_GPIO_PORT, LCD_D7_PIN, (data >> 3) & 0x01);
  GPIO_SetBits(LCD_GPIO_PORT, LCD_E_PIN);
  delayUs(LCD_DATA_DELAY);
  GPIO_ResetBits(LCD_GPIO_PORT, LCD_E_PIN);
	
}

/*
* Function: LCD_SendString
* Description: Pass data to function LCD_SendData on condition with space
* Input:
*   str: Characters to be transmitted
* Output:
*   None
*/
void LCD_SendString(char* str) {
	
  while (*str) {
    if (*str == ' ') {
      // Send space character
      LCD_SendData(' ');
    } 
		else {
      // Send non-space character
      LCD_SendData(*str);
    }
    str++;
		
  }
}

