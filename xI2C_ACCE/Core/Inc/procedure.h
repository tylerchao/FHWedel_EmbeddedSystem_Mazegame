/*
 * procedure.h
 *
 * This file is responsible to manage the game start and executing the whole game by checking goal condition and wall condition.
 *
 *
 *  Created on: 21 Jan 2022
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_PROCEDURE_H_
#define INC_PROCEDURE_H_
#include "maps.h"

extern int level;
extern uint32_t counter;
extern int point;

/**
 * start game by calling startGame() which will select one map.
 * And also start a internal clock.
 */
extern void playgame(int level);

/**
 * while the game is executing, check the goal condition and the condition of touching the walls.
 *
 */
extern void gameRunning(void);

#endif /* INC_PROCEDURE_H_ */
