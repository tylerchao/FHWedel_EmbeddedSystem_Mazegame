/*
 * procudure.c
 *
 *  Created on: 21 Jan 2022
 *      Author: Chien-hsun, Chao
 */
#include "app.h"
#include "maps.h"
#include "ball.h"
#include "gameLogic.h"
#include "main.h"
#include "lcd.h"
#include "connect.h"
#include "score.h"
#include <string.h>
#include <stdint.h>

UART_HandleTypeDef huart2;


int level = 0;
int point = 0;
uint32_t counter;

static uint32_t start_time;
static int tempscore = 0;

/**
 * start game with one of the maps.
 * By comparing the map name with the given name, and decide it.
 */
static void startGame(int name) {

	if (name == 1) {
		map1();
	} else if (name == 2) {
		map2();
	} else if (name == 3) {
		map3();
	} else if (name == 4) {
		map4();
	}
}

/**
 *  start internal clock
 */
static void counter_start(void) {
	start_time = HAL_GetTick();
}

/**
 * minus current time and get the difference of the time
 */
static uint32_t counter_getCount(void) {

	return HAL_GetTick() - start_time;
}

void playgame(int level) {
	// start with the current map.
	startGame(mapsArray[level]);

	// start counter
	counter_start();
}

void gameRunning() {

	tilting();

	//get time millisecond in every round
	counter = counter_getCount();

	if (isTouchWall(level) == 1) {

		// restart from first map
		level = 0;

		tempscore = point;
		point = tempscore + 0;

		allwhite();

		failureScore(point);
		HAL_Delay(2000);

		// reset point to 0
		point = 0;

		app_game();
	}

	if (isBallReachGoal(level) == 1) {

		//depends on the time and decide the point player will get
		point = cal_score(counter);

		ChangingScenery();
		HAL_Delay(1000);

		if (level >= 3) {

			//if level is the last level then clear to 0.
			level = 0;

			goalScore(point);
			HAL_Delay(2000);

			// reset point to 0
			point = 0;
			app_game();

		} else {
			//ready to move next level
			level++;

			app_game();
		}
	}
}

