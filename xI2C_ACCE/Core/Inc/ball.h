/*
 * ball.h
 * This file includes several functions to create a ball on the LCD screen.
 * For example, a function LCD_draw_dot to light up or light off a pixel.
 * And a function to create a ball with required size and a function clear every positions of the ball.
 * The last, there are eight functions to guide the direction of the ball when it is being moving.
 *
 *
 *  Created on: Dec 16, 2021
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_BALL_H_
#define INC_BALL_H_
#include <stdint.h>
#include "connect.h"

// An array to record the starting position of the ball.
extern uint8_t record_coord[4];

/**
 * light-up a pixel or light off a pixel
 */
extern void LCD_draw_dot(uint8_t col, uint8_t raw, uint8_t color);

/**
 * create a pixel ball with required ball size.
 */
extern void LCD_Create_Ball(int start_x, int start_y, int ballsize);

/**
 * cleaning the previous position of the ball
 */
extern void LCD_Clean_Ball(int start_col, int start_raw, int ballsize);

/**
 *  moving ball to left
 *
 *  Also, dealing with left border of the LCD screen.
 */
extern void moving_ball_horizontal_left(void);

/**
 *  moving ball to right
 *
 *  Also, dealing with right border of the LCD screen.
 */
extern void moving_ball_horizontal_right(void);

/**
 * moving ball to up
 *
 * Also, dealing with top border of the LCD screen.
 */
extern void moving_ball_vertical_up(void);

/**
 * moving ball to down
 *
 * Also, dealing with bottom border of the LCD screen.
 */
extern void moving_ball_vertical_down(void);

/**
 * moving ball to left-top
 *
 * Also, dealing with border of the LCD screen when the ball moves with left-top direction.
 */
extern void moving_ball_left_top();

/**
 * moving ball to left-bottom
 *
 * Also, dealing with border of the LCD screen when the ball moves with left-top direction.
 */
extern void moving_ball_left_bottom();

/**
 * moving ball to right-top
 *
 * Also, dealing with border of the LCD screen when the ball moves with left-top direction.
 */
extern void moving_ball_right_top();

/**
 * moving ball to right-bottom
 *
 * Also, dealing with border of the LCD screen when the ball moves with left-top direction.
 */
extern void moving_ball_right_bottom();

#endif /* INC_BALL_H_ */
