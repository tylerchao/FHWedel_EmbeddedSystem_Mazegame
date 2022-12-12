/*
 * maps.h
 *
 * Due to the maps being designed by the designer, the walls in the maps are fixed in the specific coordinates also their exits are fixed.
 * Therefore, we still need a few functions to show these walls and exits on the LCD screen.
 * In general, the purpose of this file is that create maps that are expected and declare several arrays to store the coordinate of those maps and exits.
 *
 *  Created on: 20 Jan 2022
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_MAPS_H_
#define INC_MAPS_H_
#include <stdint.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
#define NUMBER_OF_STRING 4
#define MAX_STRING_SIZE 4

uint8_t mapsArray[NUMBER_OF_STRING];

/**
 *  the coordinates of four maps
 */
extern uint8_t map_1[12][4];
extern uint8_t map_2[15][4];
extern uint8_t map_3[14][4];
extern uint8_t map_4[14][4];

/**
 * the coordinate of four different exits
 */
extern uint8_t exit_1[4];
extern uint8_t exit_2[4];
extern uint8_t exit_3[4];
extern uint8_t exit_4[4];

/**
 * A function to create different size of rectangular by using start column row and end column and row.
 */
extern void Create_rectangular(uint8_t b_p_start_col, uint8_t b_p_start_raw,
		uint8_t b_p_end_col, uint8_t b_p_end_raw);

/**
 * A function to create exit of different maps by using start column row and end column and row.
 */
extern void Create_exit(uint8_t cross_1_x, uint8_t cross_1_y, uint8_t cross_2_x,
		uint8_t cross_2_y);

/**
 * create map 1
 */
extern void map1(void);

/**
 * create map 2
 */
extern void map2(void);

/**
 * create map 3
 */
extern void map3(void);

/**
 * create map 4
 */
extern void map4(void);

#endif /* INC_MAPS_H_ */
