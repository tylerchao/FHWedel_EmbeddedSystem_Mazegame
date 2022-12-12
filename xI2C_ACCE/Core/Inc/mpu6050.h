/*
 * acc.h
 *
 *The project is completed using mpu6050 to detect the accelerometer rotating difference to control how is a ball tilting around.
 *The So this file plays an important role that analyzing the accelerometer and also calculating its titling angle by three axes.
 *The It shows these measured values on the laptop in order to efficiently realize how the direction of the ball should be set up.
 *
 *  Created on: Nov 22, 2021
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_MPU60505_H_
#define INC_MPU60505_H_

#include "app.h"

extern int16_t AX; // THE acceleration on the X axis in mg(i.e. 1000 for 1g)
extern int16_t AY; // THE acceleration on the Y axis in mg(i.e. 1000 for 1g)
extern int16_t AZ; // THE acceleration on the Z axis in mg(i.e. 1000 for 1g)
extern int16_t TX; // The tilt angle on the X axis in 1/10 (i.e. 200 for 20)
extern int16_t TY; // The tilt angle on the Y axis in 1/10 (i.e. 200 for 20)

extern int16_t AX_raw;
extern int16_t AY_raw;
extern int16_t AZ_raw;



/**
 * Initialising MPU6050 device,
 * read every specific register from the device that can help us to set up the configuration of activating this sensor.
 */
extern int MPU6050_init(void);


/**
 * Accelerometers are more sensitive to small changes in tilt when they are perpendicular to gravity.
 * Past about 45 degrees of tilt they become increasingly less sensitive.
 */
extern void MPU6050_read_accel(void);

/**
 * the component of gravity acting on the x axis is a sine function
 * and the y axis is a cosine function.
 *
 * when the sensitivity of the x axis starts dropping off after 45 degree,
 * the sensitivity of the y axis is increasing.
 *
 * For accurate measurements of tilt in the x and y planes we therefore need a 3 axis accelerometer
 *
 * AX = arctan(x/sqrt(y^2+z^2)))    roll
 * AY = arctan(y/sqrt(x^2+z^2)))     pitch
 */
extern void MPU6050_tilt_angle(void);

#endif /* INC_MPU60505_H_ */
