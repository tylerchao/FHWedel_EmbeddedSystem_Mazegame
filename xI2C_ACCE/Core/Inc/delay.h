/*
 * delay.h
 *
 * This is file is created for a delay function. Due to the reason that the HAL_DELAY only provide the millisecond delay,
 * yet the activation of LCD needs microsecond delay to initialise device. Thus, delay_us() is created.
 *
 *
 *  Created on: Dec 21, 2021
 *      Author: Chien-hsun, Chao
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

/**
 * initialise timer1 delay
 */
extern void delay_Init(void);

/**
 * using timer1 to create microsecond delay
 * The counter in the TIM1 is set to 0
 * The counter keeps counting, until the us value has been reached
 * each count takes 1 us, and therefore the counter will keep counting in microseconds until the input value has reached.
 * Once it happens, the control will come out of the loop, and we have had achieved the delay.
 *
 * from: https://controllerstech.com/create-1-microsecond-delay-stm32/
 */
extern void delay_us(uint16_t us);

#endif /* INC_DELAY_H_ */
