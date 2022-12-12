/*
 * score.h
 *
 * As the game begins to the end, whatever how is the result go, there must be a score to present the player's effort.
 * The way of doing this is to score, and this file mainly manages the final score.
 * It contains many arrays of signs and functions to create different scores of signs.
 *
 *
 *  Created on: 6 Feb 2022
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_SCORE_H_
#define INC_SCORE_H_

/**
 * when ball touch walls, a failure screen display will be shown with the current score player got.
 */
extern void failureScore(int point);

/**
 *when ball reach goal, a success sign is displayed with the current score player got.
 */
extern void goalScore(int point);

#endif /* INC_SCORE_H_ */
