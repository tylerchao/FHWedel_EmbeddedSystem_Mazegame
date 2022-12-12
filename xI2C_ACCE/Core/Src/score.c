/*
 * score.c
 *
 *
 *  Created on: 6 Feb 2022
 *      Author: Chien-hsun, Chao
 */

#include "maps.h"
#include "score.h"
#include "ball.h"

static uint8_t Gameover[30][4] = { { 30, 9, 35, 9 }, { 30, 10, 30, 18 }, { 30,
		18, 35, 18 }, { 35, 15, 35, 18 }, { 40, 12, 44, 12 },
		{ 44, 13, 44, 18 }, { 40, 15, 44, 15 }, { 40, 15, 40, 18 }, { 40, 18,
				44, 18 }, { 49, 13, 54, 13 }, { 49, 14, 49, 18 }, { 52, 13, 52,
				18 }, { 54, 13, 54, 18 }, { 59, 13, 65, 13 },
		{ 59, 14, 59, 18 }, { 59, 16, 65, 16 }, { 65, 13, 65, 16 }, { 59, 18,
				65, 18 }, { 70, 13, 75, 13 }, { 70, 13, 70, 18 }, { 75, 13, 75,
				18 }, { 70, 18, 75, 18 }, { 90, 13, 90, 18 },
		{ 90, 13, 95, 13 }, { 95, 13, 95, 16 }, { 90, 16, 95, 16 }, { 90, 18,
				95, 18 }, { 101, 13, 101, 18 }, { 102, 13, 105, 13 } };

static uint8_t v[2][4] = { { 80, 13, 80, 16 }, { 85, 13, 85, 16 } };

static uint8_t score[21][4] = { { 30, 34, 35, 34 }, { 30, 34, 30, 38 }, { 30,
		38, 35, 38 }, { 35, 38, 35, 42 }, { 30, 42, 35, 42 },
		{ 40, 36, 45, 36 }, { 40, 36, 40, 42 }, { 40, 42, 45, 42 }, { 50, 36,
				55, 36 }, { 50, 36, 50, 42 }, { 55, 36, 55, 42 }, { 50, 42, 55,
				42 }, { 60, 36, 65, 36 }, { 60, 36, 60, 42 },
		{ 70, 36, 75, 36 }, { 70, 36, 70, 42 }, { 75, 36, 75, 39 }, { 70, 39,
				75, 39 }, { 70, 42, 75, 42 }, { 80, 36, 80, 37 }, { 80, 42, 80,
				43 } };

static uint8_t success[30][4] = { { 30, 9, 35, 9 }, { 30, 9, 30, 14 }, { 30, 14,
		35, 14 }, { 35, 14, 35, 19 }, { 30, 19, 35, 19 }, { 40, 12, 40, 19 }, {
		40, 19, 45, 19 }, { 45, 12, 45, 19 }, { 50, 12, 55, 12 }, { 50, 12, 50,
		19 }, { 50, 19, 55, 19 }, { 60, 12, 65, 12 }, { 60, 12, 60, 19 }, { 60,
		19, 65, 19 }, { 70, 12, 75, 12 }, { 70, 12, 70, 19 },
		{ 70, 15, 75, 15 }, { 75, 12, 75, 15 }, { 70, 19, 75, 19 }, { 80, 12,
				85, 12 }, { 80, 12, 85, 12 }, { 80, 12, 80, 15 }, { 80, 15, 85,
				15 }, { 85, 15, 85, 19 }, { 80, 19, 85, 19 },
		{ 90, 12, 95, 12 }, { 90, 12, 90, 15 }, { 90, 15, 95, 15 }, { 95, 15,
				95, 19 }, { 90, 19, 95, 19 } };

static uint8_t zero[4][4] = { { 85, 36, 90, 36 }, { 85, 36, 85, 42 }, { 90, 36,
		90, 42 }, { 85, 42, 90, 42 } };

static uint8_t one[1][4] = { { 85, 36, 85, 42 } };

static uint8_t two[5][4] = { { 85, 36, 90, 36 }, { 90, 36, 90, 39 }, { 85, 39,
		90, 39 }, { 85, 39, 85, 42 }, { 85, 42, 90, 42 } };

static uint8_t three[5][4] = { { 85, 36, 90, 36 }, { 90, 36, 90, 39 }, { 85, 39,
		90, 39 }, { 90, 39, 90, 42 }, { 85, 42, 90, 42 } };

static uint8_t four[3][4] = { { 85, 36, 85, 39 }, { 85, 39, 90, 39 }, { 90, 36,
		90, 42 } };

static uint8_t five[5][4] = { { 85, 36, 90, 36 }, { 85, 36, 85, 39 }, { 85, 39,
		90, 39 }, { 90, 39, 90, 42 }, { 85, 42, 90, 42 } };

static uint8_t six[6][4] = { { 85, 36, 90, 36 }, { 85, 36, 85, 39 }, { 85, 39,
		90, 39 }, { 90, 39, 90, 42 }, { 85, 42, 90, 42 }, { 85, 39, 85, 42 } };

static uint8_t seven[2][4] = { { 85, 36, 90, 36 }, { 90, 36, 90, 42 } };

static uint8_t eight[7][4] = { { 85, 36, 90, 36 }, { 85, 36, 85, 39 }, { 85, 39,
		90, 39 }, { 90, 39, 90, 42 }, { 85, 42, 90, 42 }, { 85, 39, 85, 42 }, {
		90, 36, 90, 39 } };

static void create_V(void) {
	for (int i = 0; i < LEN(v); i++) {
		Create_rectangular(v[i][0], v[i][1], v[i][2], v[i][3]);
	}

	LCD_draw_dot(80, 16, 1);
	LCD_draw_dot(81, 17, 1);
	LCD_draw_dot(82, 18, 1);
	LCD_draw_dot(85, 16, 1);
	LCD_draw_dot(84, 17, 1);
	LCD_draw_dot(83, 18, 1);

}

static void create_Gameover(void) {

	for (int i = 0; i < LEN(Gameover); i++) {
		Create_rectangular(Gameover[i][0], Gameover[i][1], Gameover[i][2],
				Gameover[i][3]);
	}

	create_V();
}

static void create_success(void) {
	for (int i = 0; i < LEN(success); i++) {
		Create_rectangular(success[i][0], success[i][1], success[i][2],
				success[i][3]);
	}
}

static void create_score_sign(void) {
	for (int i = 0; i < LEN(score); i++) {
		Create_rectangular(score[i][0], score[i][1], score[i][2], score[i][3]);
	}

}

static void create_zero() {
	for (int i = 0; i < LEN(zero); i++) {
		Create_rectangular(zero[i][0], zero[i][1], zero[i][2], zero[i][3]);
	}
}

static void create_one() {
	for (int i = 0; i < LEN(one); i++) {
		Create_rectangular(one[i][0], one[i][1], one[i][2], one[i][3]);
	}
}

static void create_two() {
	for (int i = 0; i < LEN(two); i++) {
		Create_rectangular(two[i][0], two[i][1], two[i][2], two[i][3]);
	}
}

static void create_three() {
	for (int i = 0; i < LEN(three); i++) {
		Create_rectangular(three[i][0], three[i][1], three[i][2], three[i][3]);
	}
}

static void create_four() {
	for (int i = 0; i < LEN(four); i++) {
		Create_rectangular(four[i][0], four[i][1], four[i][2], four[i][3]);
	}
}

static void create_five() {
	for (int i = 0; i < LEN(five); i++) {
		Create_rectangular(five[i][0], five[i][1], five[i][2], five[i][3]);
	}
}

static void create_six() {
	for (int i = 0; i < LEN(six); i++) {
		Create_rectangular(six[i][0], six[i][1], six[i][2], six[i][3]);
	}
}

static void create_seven() {
	for (int i = 0; i < LEN(seven); i++) {
		Create_rectangular(seven[i][0], seven[i][1], seven[i][2], seven[i][3]);
	}
}

static void create_eight() {
	for (int i = 0; i < LEN(eight); i++) {
		Create_rectangular(eight[i][0], eight[i][1], eight[i][2], eight[i][3]);
	}
}

static void final_score(int point) {
	switch (point) {
	case 0:
		create_zero();
		break;
	case 1:
		create_one();
		break;
	case 2:
		create_two();
		break;
	case 3:
		create_three();
		break;
	case 4:
		create_four();
		break;
	case 5:
		create_five();
		break;
	case 6:
		create_six();
		break;
	case 7:
		create_seven();
		break;
	case 8:
		create_eight();
		break;

	}
}

void failureScore(int point) {
	create_Gameover();
	create_score_sign();
	final_score(point);
}

void goalScore(int point) {
	create_success();
	create_score_sign();
	final_score(point);
}
