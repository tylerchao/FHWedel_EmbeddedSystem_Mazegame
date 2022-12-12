/*
 * delay.c
 *
 *  Created on: Dec 21, 2021
 *      Author: Chien-hsun, Chao
 */
#include "main.h"

TIM_HandleTypeDef htim1;

void delay_Init(){
	HAL_TIM_Base_Start(&htim1);
}

/**
 * using timer1 to create microsecond delay
 * The counter in the TIM1 is set to 0
 * The counter keeps counting, until the us value has been reached
 * each count takes 1 us, and therefore the counter will keep counting in microseconds until the input value has reached.
 * Once it happens, the control will come out of the loop, and we have had achieved the delay.
 *
 * from: https://controllerstech.com/create-1-microsecond-delay-stm32/
 */
void delay_us(uint16_t us) {

	__HAL_TIM_SET_COUNTER(&htim1, 0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us)
		;  // wait for the counter to reach the us input in the parameter

}
