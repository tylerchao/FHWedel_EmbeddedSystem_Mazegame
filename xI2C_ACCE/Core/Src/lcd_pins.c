/*
 * lcd_pins.c
 *
 *  Created on: Dec 15, 2021
 *      Author: Chien-hsun, Chao
 */
#include "lcd_pins.h"
#include "app.h"
#include "main.h"
/**
 *  reset =1
 */
void RST_1(void) {
	HAL_GPIO_WritePin(GPIOC, RST_Pin, GPIO_PIN_SET);
}

/**
 * 	DI = 0
 */
void DI_0(void) {
	HAL_GPIO_WritePin(GPIOC, DI_Pin, GPIO_PIN_RESET);
}

/**
 * RW = 0
 */
void RW_0(void) {
	HAL_GPIO_WritePin(GPIOC, RW_Pin, GPIO_PIN_RESET);
}

/**
 * EN = 0
 */
void EN_0(void) {
	HAL_GPIO_WritePin(GPIOC, EN_Pin, GPIO_PIN_RESET);
}

/**
 * EN = 1
 */
void EN_1(void) {
	HAL_GPIO_WritePin(GPIOC, EN_Pin, GPIO_PIN_SET);
}

/**
 * Activate CS1, CS2 Left and right side screen
 * CS1 = 1, CS2 = 1
 */
void activate_CS1_CS2(void) {
	HAL_GPIO_WritePin(GPIOC, CS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, CS2_Pin, GPIO_PIN_SET);
}

/**
 * DI = 1
 * RW = 0
 *
 * write display data operation
 */
void write_display_data(void) {
	HAL_GPIO_WritePin(GPIOC, DI_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, RW_Pin, GPIO_PIN_RESET);
}

/**
 * DI = 0
 * RW = 0
 *
 * write display command operation
 */
void write_display_command(void) {
	HAL_GPIO_WritePin(GPIOC, DI_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, RW_Pin, GPIO_PIN_RESET);
}

/**
 * left side
 */
void leftSide_Screen(void) {
	HAL_GPIO_WritePin(GPIOC, CS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, CS2_Pin, GPIO_PIN_RESET);
}

/**
 * right side
 */
void rightSide_Screen(void) {
	HAL_GPIO_WritePin(GPIOC, CS1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, CS2_Pin, GPIO_PIN_SET);
}
