/*
 * app.c
 *
 *  Created on: Nov 22, 2021
 *      Author: Chien-Hsun, Chao
 */

#include "app.h"
#include "main.h"
#include "mpu6050.h"
#include "stdio.h"
#include "timer.h"
#include "string.h"
#include "lcd.h"
#include "ball.h"
#include "connect.h"
#include "maps.h"
#include "procedure.h"
#include "score.h"

UART_HandleTypeDef huart2;

#define PRINT_MESSAGE_DLY 200

static char print_Buffer_accel[64];
static int16_t buffer_accel_X[DATA_AMOUNT];
static int16_t buffer_accel_Y[DATA_AMOUNT];
static int16_t buffer_accel_Z[DATA_AMOUNT];
static int16_t buffer_angle_x[DATA_AMOUNT];
static int16_t buffer_angle_y[DATA_AMOUNT];

static int16_t AX_final;
static int16_t AY_final;
static int16_t AZ_final;
static int16_t TX_final;
static int16_t TY_final;

int16_t angle_buffer_output[2] = { 0, 0 };
int16_t accel_buffer_output[3] = { 0, 0, 1060 };

int16_t update_angle_buffer_output[2] = { 0, 0 };
int16_t update_accel_buffer_output[3] = { 0, 0, 1060 };

static void uart_Print_accel() {
	sprintf(print_Buffer_accel,
			"AX: %5d; AY: %5d; AZ: %5d; TX: %5d; TY: %5d \n", AX, AY, AZ, TX,
			TY);
	HAL_UART_Transmit(&huart2, (uint8_t*) print_Buffer_accel,
			strlen(print_Buffer_accel),
			HAL_MAX_DELAY);

}

static int16_t accel_average(int16_t *buffer) {
	int16_t counter = 0;
	int16_t result;
	for (int j = 0; j < sizeof(buffer); j++) {
		counter = counter + buffer[j];
	}

	result = counter / sizeof(buffer);
	return result;
}

static void update_buffer(int16_t AX, int16_t AY, int16_t AZ, int16_t TX,
		int16_t TY) {
	update_accel_buffer_output[0] = accel_buffer_output[0];
	update_accel_buffer_output[1] = accel_buffer_output[1];
	update_accel_buffer_output[2] = accel_buffer_output[2];

	update_angle_buffer_output[0] = angle_buffer_output[0];
	update_angle_buffer_output[1] = angle_buffer_output[1];

	accel_buffer_output[0] = AX;
	accel_buffer_output[1] = AY;
	accel_buffer_output[2] = AZ;

	angle_buffer_output[0] = TX;
	angle_buffer_output[1] = TY;

}

static void counting_average(void) {
	for (int i = 0; i < DATA_AMOUNT; i++) {
		MPU6050_read_accel();
		MPU6050_tilt_angle();
		buffer_accel_X[i] = AX;
		buffer_accel_Y[i] = AY;
		buffer_accel_Z[i] = AZ;
		buffer_angle_x[i] = TX;
		buffer_angle_y[i] = TY;
	}

	AX_final = accel_average(buffer_accel_X);
	AY_final = accel_average(buffer_accel_Y);
	AZ_final = accel_average(buffer_accel_Z);
	TX_final = accel_average(buffer_angle_x);
	TY_final = accel_average(buffer_angle_y);

	AX = AX_final;
	AY = AY_final;
	AZ = AZ_final;
	TX = TX_final;
	TY = TY_final;

	update_buffer(AX, AY, AZ, TX, TY);
}

void app_init(void) {
	MPU6050_init();
	timer_init();
	timer_register(uart_Print_accel, PRINT_MESSAGE_DLY);
	LCD_Init();
	LCD_CleanBoard();
	intialise_ball_starting_pos();
}

void app_game(void) {
	LCD_CleanBoard();
	intialise_ball_starting_pos();
	playgame(level);
}

void app_loop(void) {
	counting_average();
	gameRunning();
}
