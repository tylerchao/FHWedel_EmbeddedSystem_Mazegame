/*
 * timer.h
 * This timer module can be used to multiplex a single hardware timer into
 * multiple software timers (i.e. periodic function calls). The number of
 * available software timers is limited to MAX_TIMERS.
 * This module must be initialized by calling timer_init() before any other
 * usage. Then, software timers (callbacks) can be registered with the function
 * timer_register(timerfkt, div). The function timer_tick() must be called with
 * the frequency TICKRATE_HZ from a hardware timer or any other reliable timing
 * source.
 *
 *  Created on: 01.11.2018
 *      Author: Timm Bostelmann
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <stdint.h>
#include "main.h"

/***Constants******************************************************************/
#define TICKRATE_HZ (1000)
#define MAX_TIMERS (8)
/******************************************************************************/

/***Types**********************************************************************/
typedef void (*fptimerfkt)(void);
/******************************************************************************/

/***Functions******************************************************************/

/*
 * Initialize the timer module.
 * Must be called before any other usage of the module.
 * All previously registered timers are deleted!
 *
 * Return: 1 for success, 0 for failure
 */
extern int timer_init(void);

/*
 * Register a new timer function.
 * The new timer function "timerfkt" is called with a frequency of
 * "TICKRATE_HZ" / "div".
 * @param timerfkt Pointer to the timer function that is to be called
 * @param div Clock divider f_out = f_in / div
 * Return: 1 for success, 0 for failure
 */
extern int timer_register(fptimerfkt timerfkt, uint32_t div);

/*
 * Process next tick.
 * Must be called periodically with a frequency of TICKRATE_HZ
 * Return: 1 for success, 0 for failure
 */
extern void timer_tick(void);

/******************************************************************************/
#endif /* TIMER_H_ */
