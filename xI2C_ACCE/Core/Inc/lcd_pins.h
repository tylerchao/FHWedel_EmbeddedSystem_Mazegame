/*
 * lcd_pins.h
 *
 * every functions here will be used to activate LCD device.
 *
 *  Created on: Dec 15, 2021
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_LCD_PINS_H_
#define INC_LCD_PINS_H_

/**
 *  reset =1
 */
extern void RST_1(void);

/**
 * 	DI = 0
 */
extern void DI_0(void);

/**
 * RW = 0
 */
extern void RW_0(void);

/**
 * EN = 0
 */
extern void EN_0(void);

/**
 * EN = 1
 */
extern void EN_1(void);

/**
 * Activate CS1, CS2 Left and right side screen
 * CS1 = 1, CS2 = 1
 */
extern void activate_CS1_CS2(void);

/**
 * DI = 1
 * RW = 0
 *
 * write display data operation
 */
extern void write_display_data(void);

/**
 * DI = 0
 * RW = 0
 *
 * write display command operation
 */
extern void write_display_command(void);

/**
 * left side
 */
extern void leftSide_Screen(void);

/**
 * right side
 */
extern void rightSide_Screen(void);

#endif /* INC_LCD_PINS_H_ */
