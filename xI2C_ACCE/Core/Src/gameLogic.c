/*
 * gameLogic.c
 *
 *  Created on: 20 Jan 2022
 *      Author: Chien-hsun, Chao
 */

#include "gameLogic.h"
#include "ball.h"
#include "maps.h"
#include "main.h"
#include "timer.h"
#include "delay.h"
#include "procedure.h"

UART_HandleTypeDef huart2;

int isBallReachGoal(int level) {

	int goal = 0;

	switch (level) {
	case 0:
		if ((record_coord[0] >= exit_1[0] && record_coord[0] <= exit_1[2]
				&& record_coord[1] >= exit_1[1]
				&& record_coord[1] <= (exit_1[1] + 7))) {
			goal = 1;
		}
		break;

	case 1:
		if ((record_coord[0] >= exit_2[0] && record_coord[0] <= exit_2[2]
				&& record_coord[1] >= exit_2[1]
				&& record_coord[1] <= (exit_2[1] + 7))) {
			goal = 1;
		}
		break;

	case 2:
		if ((record_coord[0] >= exit_3[0] && record_coord[0] <= exit_3[2]
				&& record_coord[1] <= (exit_3[0] + 7)
				&& record_coord[1] >= exit_3[1])) {
			goal = 1;
		}
		break;

	case 3:
		if ((record_coord[0] >= exit_4[0] && record_coord[0] <= exit_4[2]
				&& record_coord[1] >= exit_4[1]
				&& record_coord[1] <= exit_4[1] + 7)) {
			goal = 1;
		}
		break;

	default:
		goal = 0;
		break;
	}

	return goal;

}

/**
 *
 * maps[][] could be map_1 ,map_2, map_3, map_4
 * size = should be the size of the col of the current map.
 */
static int checkingballCollision(uint8_t maps[][4], int size) {
	int collision = 0;
	for (int i = 0; i < size; i++) {
		if ((record_coord[0] >= maps[i][0] && record_coord[0] <= maps[i][2]
				&& record_coord[1] >= maps[i][1]
				&& record_coord[1] <= maps[i][3])
				|| (record_coord[2] >= maps[i][0]
						&& record_coord[2] <= maps[i][2]
						&& record_coord[3] >= maps[i][1]
						&& record_coord[3] <= maps[i][3])
				|| (record_coord[0] >= maps[i][0]
						&& record_coord[0] <= maps[i][2]
						&& record_coord[3] >= maps[i][1]
						&& record_coord[3] <= maps[i][3])
				|| (record_coord[2] >= maps[i][0]
						&& record_coord[2] <= maps[i][2]
						&& record_coord[1] >= maps[i][1]
						&& record_coord[1] <= maps[i][3])) {
			collision = 1;
		}
	}
	return collision;
}

int isTouchWall(int level) {
	int Touch = 0;

	switch (level) {
	case 0:
		Touch = checkingballCollision(map_1, LEN(map_1));
		break;
	case 1:
		Touch = checkingballCollision(map_2, LEN(map_2));
		break;
	case 2:
		Touch = checkingballCollision(map_3, LEN(map_3));
		break;
	case 3:
		Touch = checkingballCollision(map_4, LEN(map_4));
		break;
	default:
		Touch = 0;

		break;
	}

	return Touch;

}

void allblack(void) {

	for (int col = 0; col < 128; col++) {
		for (int raw = 0; raw < 64; raw++) {

			LCD_draw_dot(col, raw, 1);
			delay_us(50);

		}
	}
}

void allwhite(void) {

	for (int col = 0; col < 128; col++) {
		for (int raw = 0; raw < 64; raw++) {

			LCD_draw_dot(col, raw, 0);
			delay_us(50);

		}
	}
}

void ChangingScenery(void) {
	allblack();
	allwhite();
}

int cal_score(int counter) {

	int minutes = counter / 1000;

	if (minutes <= GAME_TIME_LIMIT) {
		point = point + POINT_2;
	} else if (minutes > GAME_TIME_LIMIT) {
		point = point + POINT_1;
	}

	return point;
}
