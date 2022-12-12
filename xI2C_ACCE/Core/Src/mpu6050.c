/*
 * accel.c
 *
 *  Created on: Nov 22, 2021
 *      Author: Chien-hsun, Chao
 */

#include "app.h"
#include "mpu6050.h"
#include "main.h"
#include <math.h>

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

#define MPU6050_I2C_ADDRESS 0xD0       // device address
#define WHO_AM_I 0x75                  // register (memory address)
#define PWR_MGMT_1 0x6B                // power management
#define ACCEL_CONFIG 0x1C              // the configuration of acceleration and it can configure the accelerometer full scale range.
#define ACCEL_XOUT_H 0x3B              // the
#define SMPLRT_DIV 0x19

// accelerometer variable
int16_t AX;
int16_t AY;
int16_t AZ;
int16_t TX;
int16_t TY;

int16_t AX_raw;
int16_t AY_raw;
int16_t AZ_raw;

float TX_raw;
float TY_raw;

static int lsb_sens = 16384 / 1000;    // LSB Sensitivity
static float rad_to_deg = 180 / M_PI;  // radius to degree

int MPU6050_init(void) {

	uint8_t check; //flag of checking
	uint8_t Data;  // the new number
	uint16_t error;

	error = HAL_I2C_Mem_Read(&hi2c1, MPU6050_I2C_ADDRESS, WHO_AM_I, 1, &check,
			1, 1000);

	if (error) {
		HAL_UART_Transmit(&huart2, (uint8_t*) "error0", 6, HAL_MAX_DELAY);
	}

	if (check == 104) {

		// set the sleep mode to 0 in order to activate the device
		Data = 0;
		error = HAL_I2C_Mem_Write(&hi2c1, MPU6050_I2C_ADDRESS, PWR_MGMT_1, 1,
				&Data, 1, 1000);

		if (error) {
			HAL_UART_Transmit(&huart2, (uint8_t*) "error1", 6, HAL_MAX_DELAY);
		} else {
			HAL_UART_Transmit(&huart2, (uint8_t*) "PWR", 3, HAL_MAX_DELAY);
		}

		// set up the configuration of the accelerometer
		// XA_ST=0, YA_ST=0, ZA_ST=0, AFS_SEL=0(+-2g)
		Data = 0x00;
		error = HAL_I2C_Mem_Write(&hi2c1, MPU6050_I2C_ADDRESS, ACCEL_CONFIG, 1,
				&Data, 1, 1000);

		if (error) {
			HAL_UART_Transmit(&huart2, (uint8_t*) "error2", 6, HAL_MAX_DELAY);
		} else {
			HAL_UART_Transmit(&huart2, (uint8_t*) "ACC", 3, HAL_MAX_DELAY);

		}

		// Sample rate divider 1kHz for DLPF_CFG : 7
		Data = 0x07;
		error = HAL_I2C_Mem_Write(&hi2c1, MPU6050_I2C_ADDRESS, SMPLRT_DIV, 1,
				&Data, 1, 1000);
		if (error) {
			HAL_UART_Transmit(&huart2, (uint8_t*) "error3", 6, HAL_MAX_DELAY);
		} else {
			HAL_UART_Transmit(&huart2, (uint8_t*) "spl", 3, HAL_MAX_DELAY);

		}

		return 0;
	} else {
		HAL_UART_Transmit(&huart2, (uint8_t*) "error4", 6,
		HAL_MAX_DELAY);
		return 1;
	}
	return 0;
}

void MPU6050_read_accel(void) {

	uint8_t buffer[6];
	uint16_t error;

	//initialise buffer to 0
	for (int i = 0; i < sizeof(buffer); i++)
		buffer[i] = 0;

	error = HAL_I2C_Mem_Read(&hi2c1, MPU6050_I2C_ADDRESS, ACCEL_XOUT_H,
	I2C_MEMADD_SIZE_8BIT, buffer, 6, 1000);

	if (error) {
		HAL_UART_Transmit(&huart2, (uint8_t*) "error5", 6, HAL_MAX_DELAY);
	}

	AX_raw = (int16_t) (buffer[0] << 8 | buffer[1]);
	AY_raw = (int16_t) (buffer[2] << 8 | buffer[3]);
	AZ_raw = (int16_t) (buffer[4] << 8 | buffer[5]);

	AX = (int16_t) ((AX_raw / lsb_sens));
	AY = (int16_t) ((AY_raw / lsb_sens));
	AZ = (int16_t) ((AZ_raw / lsb_sens));

}

void MPU6050_tilt_angle(void) {

	TX_raw = (float) (atan(AX_raw / sqrt(pow(AY_raw, 2) + pow(AZ_raw, 2))));
	TY_raw = (float) (atan(AY_raw / sqrt(pow(AX_raw, 2) + pow(AZ_raw, 2))));

	TX = (int) (TX_raw * rad_to_deg * 10);
	TY = (int) (TY_raw * rad_to_deg * 10);

}

