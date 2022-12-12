/*
 * connect.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Chien-hsun, Chao
 */

#include "app.h"
#include "main.h"
#include "timer.h"
#include "lcd.h"
#include "ball.h"
#include "connect.h"
#include "delay.h"
#include <stdlib.h>

/**
 *  checking if the accelerometer is on the 1g circumstance.
 */
static int Is_One_G(void) {
	int data_gravity = 1050;
	int range_bias_min = 0;
	int range_bias_max = 15;
	int bias_az = abs(accel_buffer_output[2] - data_gravity);
	int one_g = 0;

	if (((bias_az >= range_bias_min) && (bias_az <= range_bias_max))) {
		one_g = 1;
	}
	return one_g;
}

/**
 * checking if the accelerometer is standstill or not.
 */
static int IsNotMoving(void) {
	int Notmove = 0;
	int Tx = abs(angle_buffer_output[0]);
	int Ty = abs(angle_buffer_output[1]);
	if (Tx < 50 && Ty < 50) {
		Notmove = 1;
	}
	return Notmove;
}

/**
 * flag = 0, left,
 * flag = 1, right
 * flag = 2, top
 * flag = 3, bottom
 * flag = 4, left-top
 * flag = 5, left-bottom
 * flag = 6, right-top
 */
static int Istitlingdirection(void) {

	int flag = 8;
	int Tx = angle_buffer_output[0];
	int Ty = angle_buffer_output[1];

	if ((Tx > 200) && (-200 < Ty) && (Ty < 200)) {  //left
		flag = 0;
	} else if ((Tx < -150) && (Ty < 200) && (Ty > -200)) {  // right
		flag = 1;
	} else if ((-150 < Tx) && (Tx < 200) && (Ty < -200)) {  // top
		flag = 2;
	} else if ((-150 < Tx) && (Tx < 200) && (Ty > 200)) {  // bottom
		flag = 3;
	} else if ((Tx > 200) && (Ty < -200)) {    // left-top
		flag = 4;
	} else if ((Tx > 200) && (Ty > 200)) { // left - bottom
		flag = 5;
	} else if ((Tx < -150) && (Ty < -200)) {    //right - top
		flag = 6;
	} else if ((Tx < -150) && (Ty > 200)) { // right -bottom
		flag = 7;
	}

	return flag;
}

/**
 * initialise a ball position and create it when the sensor is lay still
 * the sensor is in the 1 G circumstance
 */
void intialise_ball_starting_pos(void) {
	uint8_t startingPosition[2] = { START_POSITION_COL, START_POSITION_RAW };
	if (Is_One_G() && IsNotMoving()) {
		LCD_Create_Ball(startingPosition[0], startingPosition[1], BALL_SIZE);
	}
	record_coord[0] = START_POSITION_COL;
	record_coord[1] = START_POSITION_RAW;
}

/**
 * moving ball
 */
void tilting(void) {
	if (Istitlingdirection() == 0) {
		moving_ball_horizontal_left();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else if (Istitlingdirection() == 1) {
		moving_ball_horizontal_right();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else if (Istitlingdirection() == 2) {
		moving_ball_vertical_up();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else if (Istitlingdirection() == 3) {
		moving_ball_vertical_down();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else if (Istitlingdirection() == 4) {
		moving_ball_left_top();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else if (Istitlingdirection() == 5) {
		moving_ball_left_bottom();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else if (Istitlingdirection() == 6) {
		moving_ball_right_top();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else if (Istitlingdirection() == 7) {
		moving_ball_right_bottom();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else {
		LCD_Create_Ball(record_coord[0], record_coord[1], BALL_SIZE);
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	}
}

void testing(void) {
	if (Istitlingdirection() == 6) {
		moving_ball_right_top();
		HAL_Delay(BALL_DELAY);
		LCD_Clean_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	} else {
		LCD_Create_Ball(record_coord[0], record_coord[1], BALL_SIZE);
	}
}
