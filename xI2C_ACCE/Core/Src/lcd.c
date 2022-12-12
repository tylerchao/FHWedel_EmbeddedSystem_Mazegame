/*
 * lcd.c
 *
 *  Created on: Dec 7, 2021
 *      Author: Chien-hsun, Chao
 */

#include "app.h"
#include "main.h"
#include "lcd.h"
#include "lcd_pins.h"
#include "delay.h"

UART_HandleTypeDef huart2;

// Command
#define DIS_ON_REGISTER 0x3F      // DISPLAY ON

// text line   (0~63) (0xC0 ~ OxFF)
#define START_LINE 0xC0

// row  (0xB8 ~ OxBF)  (Page 0 to page 7)
#define PAGE_ADDRESS 0xb8

// column (0~63) (0x40 ~ 0x7F)
#define COL_ADDRESS 0x40

void LCD_Init(void) {

	RST_1();
	DI_0();
	RW_0();
	EN_0();
	delay_us(20);

	activate_CS1_CS2();
	LCD_WriteCommand(DIS_ON_REGISTER);
	LCD_WriteCommand(PAGE_ADDRESS);
	LCD_WriteCommand(COL_ADDRESS);
	delay_us(20);


}

void LCD_WriteData(uint8_t data) {
	write_display_data();
	delay_us(20);

	GPIOC->ODR = (GPIOC->ODR & 0xFF00) | data; //0xFF00 is the 1111 1111 0000 0000  Clean the lowest 8 bit
											   // and store cmd data into output data register
	EN_1();
	delay_us(20);

	EN_0();
	delay_us(20);
}

void LCD_WriteCommand(uint8_t cmd) {

	write_display_command();
	delay_us(20);

	GPIOC->ODR = (GPIOC->ODR & 0xFF00) | cmd; //0xFF00 is the 1111 1111 0000 0000  Clean the lowest 8 bit
											  // and store cmd data into output data register

	EN_1();
	delay_us(20);

	EN_0();
	delay_us(20);
}

/**
 * Clear all the noise and set every pixel to 0.
 */
void LCD_CleanBoard(void) {
	write_display_data();
	for (int raw = 0; raw < 8; raw++) {
		for (int col = 0; col < 128; col++) {
			LCD_Set_Position(col, raw);
			LCD_WriteData(ONE_PIXEL_OFF);
		}
	}
}

/**
 * version 1: x: 0 ~ 127, y: 0 ~ 7
 * version 2: x: 0 ~ 127, y: 0 ~ 63 when the cal_page_address is being used.
 *
 */
void LCD_Set_Position(uint8_t col, uint8_t raw) {

	if (col < 128 && raw < 64) {
		if (col >= 64) {
			rightSide_Screen();
			LCD_WriteCommand(PAGE_ADDRESS + raw); //Y Coordinate, page address
			LCD_WriteCommand(COL_ADDRESS + (col - 64)); //X Coordinate,

		} else {
			leftSide_Screen();
			LCD_WriteCommand(PAGE_ADDRESS + raw); //Y Coordinate, page address
			LCD_WriteCommand(COL_ADDRESS + col); //X Coordinate,

		}
	} else {
		HAL_UART_Transmit(&huart2, (uint8_t*) "input out of range", 18,
		HAL_MAX_DELAY);
	}

}

/**
 * decide which raw
 *  0-63
 */
int cal_Page_address(int raw) {
	int page = raw / 8;
	return page;
}

/**
 * decide how many shifting for one pixel
 */
static int cal_pixel_shifting(int raw) {
	int shiftingnumber = raw % 8;
	return shiftingnumber;
}

/**
 * shifting one to the required position
 */
static uint8_t cal_hex_of_shifting(int shiftingnumber) {
	uint8_t data;
	data = 0x01 << shiftingnumber;
	return data;
}

/**
 * add a new data of the position to the previous data
 */
uint8_t cal_adding_previous_pixel_position(uint8_t data, uint8_t raw) {
	data = data | cal_hex_of_shifting(cal_pixel_shifting(raw));
	return data;
}

/**
 * vanish the previous position
 */
uint8_t cal_vanish_previous_pixel_position(uint8_t data) {
	data = data & ONE_PIXEL_OFF;
	return data;
}



