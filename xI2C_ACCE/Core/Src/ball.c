/*
 * ball.c
 *
 *  Created on: Dec 16, 2021
 *      Author: Chien-hsun, Chao
 */
#include "app.h"
#include "main.h"
#include "lcd.h"
#include "lcd_pins.h"
#include "maps.h"
#include "connect.h"

//constant
#define COL_MAX (128)
#define COL_MIN (0)
#define RAW_MAX (64)
#define RAW_MIN (0)

static uint8_t RAM_buffer[128][8] = { 0 };
uint8_t record_coord[4] = { 0 };

/**
 *  col: 0 ~ 127
 *  raw: 0 ~ 64
 *  color: 1(on) 0(off )
 */
void LCD_draw_dot(uint8_t col, uint8_t raw, uint8_t color) {
	uint8_t data;
	if ((col >= COL_MAX) || (raw >= RAW_MAX)) {
		return;
	}

	LCD_Set_Position(col, cal_Page_address(raw));

	if (color == 1) {
		data = RAM_buffer[col][cal_Page_address(raw)];

		data = cal_adding_previous_pixel_position(data, raw);

		LCD_WriteData(data);

		RAM_buffer[col][cal_Page_address(raw)] = data;
	} else if (color == 0) {
		data = RAM_buffer[col][cal_Page_address(raw)];

		data = cal_vanish_previous_pixel_position(data);

		LCD_WriteData(data);

		RAM_buffer[col][cal_Page_address(raw)] = data;
	}
}

static void create_diff_ball_size(int start_col, int start_raw, int ballsize) {
	for (uint8_t i = start_col; i <= (ballsize + start_col); i++) {

		for (uint8_t j = start_raw; j <= (ballsize + start_raw); j++) {

			LCD_draw_dot(i, j, 1);

		}
	}
}

static void clean_diff_ball_size(int start_col, int start_raw, int ballsize) {
	for (uint8_t i = start_col; i <= (ballsize + start_col); i++) {

		for (uint8_t j = start_raw; j <= (ballsize + start_raw); j++) {

			LCD_draw_dot(i, j, 0);

		}
	}
}

/**
 * create a pixel ball
 */
void LCD_Create_Ball(int start_col, int start_raw, int ballsize) {

	write_display_data();

	if (ballsize > 4 || ballsize < 0) {
		ballsize = 2;
	}

	create_diff_ball_size(start_col, start_raw, ballsize);

	record_coord[0] = start_col;
	record_coord[1] = start_raw;
	record_coord[2] = (start_col + ballsize);
	record_coord[3] = (start_raw + ballsize);
}

/**
 * cleaning the previous position of the ball
 */
void LCD_Clean_Ball(int start_col, int start_raw, int ballsize) {

	write_display_data();

	if (ballsize > 4 || ballsize < 0) {
		ballsize = 2;
	}

	clean_diff_ball_size(start_col, start_raw, ballsize);

}

/**
 * moving ball to left
 */
void moving_ball_horizontal_left(void) {

	int start_col = record_coord[0];
	int start_raw = record_coord[1];

	int CountingBlock = 1;
	int new_col = start_col - CountingBlock;

	if (new_col < COL_MIN) {
		new_col = start_col;

		LCD_Create_Ball(new_col, start_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(new_col, start_raw, BALL_SIZE);

	}
	record_coord[0] = new_col;
	record_coord[1] = start_raw;

}

/**
 * moving ball to right
 */
void moving_ball_horizontal_right(void) {

	int start_col = record_coord[0];
	int start_raw = record_coord[1];
	int end_col = record_coord[2];

	int CountingBlock = 1;
	int new_end_col = end_col + CountingBlock;
	int new_start_col = start_col + CountingBlock;

	if (new_end_col >= COL_MAX) {
		new_start_col = start_col;

		LCD_Create_Ball(new_start_col, start_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(new_start_col, start_raw, BALL_SIZE);

	}

	record_coord[0] = new_start_col;
	record_coord[1] = start_raw;

}

/**
 *  moving ball to up
 */
void moving_ball_vertical_up(void) {

	int start_col = record_coord[0];
	int start_raw = record_coord[1];

	int CountingBlock = 1;
	int new_raw = start_raw - CountingBlock;

	if (new_raw < RAW_MIN) {
		new_raw = start_raw;

		LCD_Create_Ball(start_col, new_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(start_col, new_raw, BALL_SIZE);

	}

	record_coord[0] = start_col;
	record_coord[1] = new_raw;

}

/**
 *  moving ball to down
 */
void moving_ball_vertical_down(void) {
	int start_col = record_coord[0];
	int start_raw = record_coord[1];
	int end_raw = record_coord[3];

	int CountingBlock = 1;

	int new_start_raw = start_raw + CountingBlock;
	int new_end_raw = end_raw + CountingBlock;

	if (new_end_raw >= RAW_MAX) {

		new_start_raw = start_raw;

		LCD_Create_Ball(start_col, new_start_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(start_col, new_start_raw, BALL_SIZE);

	}

	record_coord[0] = start_col;
	record_coord[1] = new_start_raw;

}

/**
 * moving to left-top
 */
void moving_ball_left_top(void) {
	int start_col = record_coord[0];
	int start_raw = record_coord[1];

	int CountingBlock = 1;
	int new_col = start_col - CountingBlock;
	int new_raw = start_raw - CountingBlock;

	if ((new_col < COL_MIN) || (new_raw < RAW_MIN)) {

		new_col = start_col;
		new_raw = start_raw;

		LCD_Create_Ball(new_col, new_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(new_col, new_raw, BALL_SIZE);

	}

	record_coord[0] = new_col;
	record_coord[1] = new_raw;

}

/**
 * moving ball to left bottom
 */
void moving_ball_left_bottom(void) {

	int start_col = record_coord[0];
	int start_raw = record_coord[1];
	int end_raw = record_coord[3];

	int CountingBlock = 1;
	int new_start_col = start_col - CountingBlock;
	int new_start_raw = start_raw + CountingBlock;
	int new_end_raw = end_raw + CountingBlock;

	if ((new_start_col < COL_MIN) || (new_end_raw >= RAW_MAX)) {
		new_start_col = start_col;
		new_start_raw = start_raw;

		LCD_Create_Ball(new_start_col, new_start_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(new_start_col, new_start_raw, BALL_SIZE);

	}

	record_coord[0] = new_start_col;
	record_coord[1] = new_start_raw;

}

/**
 * moving ball to right top
 */
void moving_ball_right_top(void) {

	int start_col = record_coord[0];
	int start_raw = record_coord[1];
	int end_col = record_coord[2];

	int CountingBlock = 1;

	int new_start_col = start_col + CountingBlock;
	int new_start_raw = start_raw - CountingBlock;
	int new_end_col = end_col + CountingBlock;

	if ((new_end_col >= COL_MAX) || (new_start_raw < RAW_MIN)) {

		new_start_col = start_col;
		new_start_raw = start_raw;

		LCD_Create_Ball(new_start_col, new_start_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(new_start_col, new_start_raw, BALL_SIZE);

	}

	record_coord[0] = new_start_col;
	record_coord[1] = new_start_raw;

}

/**
 * moving ball to right bottom
 */
void moving_ball_right_bottom(void) {

	int start_col = record_coord[0];
	int start_raw = record_coord[1];
	int end_col = record_coord[2];
	int end_raw = record_coord[3];

	int CountingBlock = 1;

	int new_start_col = start_col + CountingBlock;
	int new_start_raw = start_raw + CountingBlock;
	int new_end_col = end_col + CountingBlock;
	int new_end_raw = end_raw + CountingBlock;

	if ((new_end_col >= COL_MAX) || (new_end_raw >= RAW_MAX)) {
		new_start_col = start_col;
		new_start_raw = start_raw;

		LCD_Create_Ball(new_start_col, new_start_raw, BALL_SIZE);

	} else {

		LCD_Create_Ball(new_start_col, new_start_raw, BALL_SIZE);

	}

	record_coord[0] = new_start_col;
	record_coord[1] = new_start_raw;

}

