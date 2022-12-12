/*
 * app.h
 * This file integrates the data-reading from the sensors, the activation of the micro-controller and the initialisation of the LCD.
 * Also, the functions in this files will be called separately in the main.c in order to reduce the complexity of the code.
 *
 *
 *  Created on: Nov 22, 2021
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_APP_H_
#define INC_APP_H_
#include "main.h"

// the amount of data for reading from the MPU6050 every round.
#define DATA_AMOUNT 20

/**
 *  A buffer to store titling angle of three axis from the accelerometer.
 */
extern int16_t angle_buffer_output[2];

/**
 * A buffer to store the value of the accelerometer of three axis from the accelerometer.
 */
extern int16_t accel_buffer_output[3];

/**
 *  A buffer to store updated angle of the three axis from the accelerometer.
 */
extern int16_t update_angle_buffer_output[2];

/**
 * A buffer to store the updated value of the accelerometer of three axis from the accelerometer.
 */
extern int16_t update_accel_buffer_output[3];

/**
 * A function to initialise every devices.
 */
extern void app_init(void);

/**
 * A function is called in the while loop in order to keep updating value.
 */
extern void app_loop(void);

/**
 * A function is created for starting a new map. The reason that creating this function independently
 * instead of coding inside the app_init() is that this function will be only called one time
 * and it will be called recursively if the situation is being required.
 */
extern void app_game(void);

#endif /* INC_APP_H_ */
