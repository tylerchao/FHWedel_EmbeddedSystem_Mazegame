/*
 * connect.h
 *
 * The file connects the ball file and other files.
 * There is a main function called tilting() which analyse the action of the ball.
 * It will be called in the app_loop() function.
 *
 * And a function to initialise the ball position when it is standstill and the accelerometer is not moving.
 *
 *
 *
 *  Created on: Dec 18, 2021
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_CONNECT_H_
#define INC_CONNECT_H_

//starting position of the ball.
#define START_POSITION_COL 0
#define START_POSITION_RAW 0

// ball size
#define BALL_SIZE 2

// how fast of moving ball.
#define BALL_DELAY 50

/**
 * initialise a ball position and create it when the sensor is lay still
 * the sensor is in the 1 G circumstance
 */
extern void intialise_ball_starting_pos(void);

/**
 * all action to moving ball
 */
extern void tilting(void);

/**
 *a function for testing moving a ball in different direction.
 */
extern void testing(void);

#endif /* INC_CONNECT_H_ */
