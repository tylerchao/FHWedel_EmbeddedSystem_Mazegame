/*
 * gameLogic.h
 *
 * This file contains every function that is used to sort the whole game logic.
 * In fact, as the game start and the ball start to be rotated, it will touch walls or reaches the goal area.
 * Since it touches the walls or arrives at the goal, the score should be calculated depending on the playing time.
 * In addition, as the scenery is changed from the map to the map or map to displaying the score,
 * an interface of changing the scenery provides a better understanding of the game situation.
 * Thus, Those conditions of those actions are required and need to be completely set up before they are being called.
 *
 *
 *
 *  Created on: 20 Jan 2022
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_GAMELOGIC_H_
#define INC_GAMELOGIC_H_
#include <stdint.h>

// The time limit of one game.
#define GAME_TIME_LIMIT 60

// points for winning a game.
#define POINT_1 1
#define POINT_2 2

/**
 * Checking if the ball reach the goal on the map.
 * 0: no reach goal
 * 1: reach goal
 */
extern int isBallReachGoal(int level);

/**
 *
 * checking if ball hit walls.
 *
 * 1: touch
 * 0: no touch
 */
extern int isTouchWall(int level);

/**
 * Turn all black in sequence
 */
extern void ChangingScenery(void);

/**
 * Turn all the scene to white.
 */
extern void allwhite(void);

/**
 * Turn all the scene to black.
 */
extern void allblack(void);

/**
 * calculate score depends on the time counter.
 */
extern int cal_score(int counter);

#endif /* INC_GAMELOGIC_H_ */
