/*
 * lcd.h
 *
 * This file contains several functions of activating LCD devices.
 * According to the LCD user manual and datasheet, there are a few pin settings needed to be initialized,
 * and a few specific registers needed to be known and be executed.
 * For instance, if the data is expected to be written into the device and be shown on the screen,
 * then a few pins of the LCD device need to be set up as a specific value.
 *
 *
 *  Created on: Dec 7, 2021
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#define ONE_PIXEL_ON 0x01
#define ONE_PIXEL_OFF 0x00

/**
 * initialise lcd and activate it
 */
extern void LCD_Init(void);

/**
 * write message to output data register
 */
extern void LCD_WriteData(uint8_t cmd);

/**
 * write command to Output data register
 */
extern void LCD_WriteCommand(uint8_t cmd);

/**
 * Clear all the noise and set every pixel to 0.
 */
extern void LCD_CleanBoard(void);

/**
 * version 1: x: 0 ~ 127, y: 0 ~ 7
 * version 2: x: 0 ~ 127, y: 0 ~ 63 when the cal_page_address is being used.
 *
 */
extern void LCD_Set_Position(uint8_t x, uint8_t y);

/**
 * decide which raw
 *  0-63
 */
extern int cal_Page_address(int raw);

/**
 * add a new data of the position to the previous data
 */
extern uint8_t cal_adding_previous_pixel_position(uint8_t data, uint8_t raw);

/**
 * vanish the previous position
 */
extern uint8_t cal_vanish_previous_pixel_position(uint8_t data);
#endif /* INC_LCD_H_ */

