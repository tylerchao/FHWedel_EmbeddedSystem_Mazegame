/*
 * maps.c
 *
 *  Created on: 20 Jan 2022
 *      Author: Chien-hsun, Chao
 */

#include "maps.h"
#include "ball.h"

#include <stdio.h>

uint8_t mapsArray[NUMBER_OF_STRING] = { 1, 2, 3, 4 };

uint8_t map_1[12][4] = { { 8, 0, 15, 39 }, { 24, 0, 31, 15 }, { 40, 0, 47, 39 },
		{ 56, 0, 63, 15 }, { 72, 0, 79, 39 }, { 88, 0, 95, 15 }, { 104, 0, 111,
				39 }, { 120, 0, 127, 15 }, { 24, 24, 31, 62 },
		{ 56, 24, 63, 63 }, { 88, 24, 95, 63 }, { 120, 24, 127, 63 } };

uint8_t map_2[15][4] = { { 8, 8, 23, 15 }, { 8, 17, 15, 31 },
		{ 16, 25, 63, 31 }, { 40, 0, 47, 23 }, { 24, 32, 31, 47 }, { 0, 40, 15,
				47 }, { 16, 56, 71, 63 }, { 48, 48, 55, 55 }, { 72, 0, 87, 7 },
		{ 80, 17, 87, 47 }, { 88, 24, 95, 31 }, { 104, 0, 111, 55 }, { 112, 24,
				119, 31 }, { 120, 8, 127, 15 }, { 120, 40, 127, 47 } };

uint8_t map_3[14][4] = { { 0, 8, 31, 15 }, { 24, 16, 31, 31 },
		{ 8, 24, 15, 63 }, { 16, 40, 23, 47 }, { 32, 48, 39, 63 }, { 40, 0, 47,
				39 }, { 56, 8, 95, 15 }, { 56, 24, 63, 63 }, { 72, 40, 79, 63 },
		{ 88, 40, 95, 63 }, { 104, 40, 111, 63 }, { 120, 40, 127, 63 }, { 88,
				24, 127, 31 }, { 112, 0, 119, 15 } };

uint8_t map_4[14][4] = { { 0, 16, 7, 39 }, { 0, 40, 87, 47 }, { 16, 0, 23, 23 },
		{ 32, 16, 39, 39 }, { 8, 48, 15, 55 }, { 24, 56, 31, 63 }, { 40, 48, 47,
				55 }, { 56, 56, 63, 63 }, { 48, 0, 55, 23 }, { 56, 16, 71, 23 },
		{ 80, 0, 87, 31 }, { 96, 8, 103, 63 }, { 112, 8, 119, 23 }, { 112, 32,
				119, 47 } };

uint8_t exit_1[4] = { 120, 16, 127, 16 };
uint8_t exit_2[4] = { 120, 0, 127, 0 };
uint8_t exit_3[4] = { 96, 56, 103, 56 };
uint8_t exit_4[4] = { 120, 24, 127, 24 };

void Create_rectangular(uint8_t b_p_start_col, uint8_t b_p_start_raw,
		uint8_t b_p_end_col, uint8_t b_p_end_raw) {

	for (uint8_t i = b_p_start_col; i <= b_p_end_col; i++) {

		for (uint8_t j = b_p_start_raw; j <= b_p_end_raw; j++) {

			LCD_draw_dot(i, j, 1);

		}
	}
}

void Create_exit(uint8_t cross_1_col, uint8_t cross_1_raw, uint8_t cross_2_col,
		uint8_t cross_2_raw) {

	for (int i = 0; i < 8; i++) {

		LCD_draw_dot(cross_1_col + i, cross_1_raw + i, 1);

		LCD_draw_dot(cross_2_col - i, cross_2_raw + i, 1);

	}

}

void map1(void) {

	for (int i = 0; i < LEN(map_1); i++) {

		Create_rectangular(map_1[i][0], map_1[i][1], map_1[i][2], map_1[i][3]);

		Create_exit(exit_1[0], exit_1[1], exit_1[2], exit_1[3]);
	}

}

void map2(void) {

	for (int i = 0; i < LEN(map_2); i++) {

		Create_rectangular(map_2[i][0], map_2[i][1], map_2[i][2], map_2[i][3]);

		Create_exit(exit_2[0], exit_2[1], exit_2[2], exit_2[3]);
	}

}

void map3(void) {

	for (int i = 0; i < LEN(map_3); i++) {

		Create_rectangular(map_3[i][0], map_3[i][1], map_3[i][2], map_3[i][3]);

		Create_exit(exit_3[0], exit_3[1], exit_3[2], exit_3[3]);
	}

}

void map4(void) {

	for (int i = 0; i < LEN(map_4); i++) {

		Create_rectangular(map_4[i][0], map_4[i][1], map_4[i][2], map_4[i][3]);

		Create_exit(exit_4[0], exit_4[1], exit_4[2], exit_4[3]);
	}

}

