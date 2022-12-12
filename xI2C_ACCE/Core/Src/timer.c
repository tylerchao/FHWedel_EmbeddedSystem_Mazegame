/*
 * timer.c
 *
 *
 *      Author: user
 */
#include "app.h"
#include <stdint.h>

/***Constants******************************************************************/
#define TICKRATE_HZ (1000)
#define MAX_TIMERS (8)
/******************************************************************************/

/***Types**********************************************************************/
typedef void (*fptimerfkt)(void);
extern UART_HandleTypeDef huart2;
uint8_t funNumber = 0; 		// used to know the number at which we are currently
/******************************************************************************/

/***Functions******************************************************************/
struct timer_function {
	int divider; //how often is the task called // how often my method is suppose to be called
	int counter;                     //when is the task called // tick
	fptimerfkt function_pointer; //reference to the function you are going to stor //how is the task called
};
struct timer_function fct[MAX_TIMERS];

/*
 * Initialize the timer module.
 * Must be called before any other usage of the module.
 * All previously registered timers are deleted!
 *
 * Return: 1 for success, 0 for failure
 */
int timer_init(void) {

	return 1;
}

/*
 * Register a new timer function.
 * The new timer function "timerfkt" is called with a frequency of
 * "TICKRATE_HZ" / "div".
 * @param timerfkt Pointer to the timer function that is to be called
 * @param div Clock divider f_out = f_in / div
 * Return: 1 for success, 0 for failure
 */
int timer_register(fptimerfkt timerfkt, uint32_t div) {

	if (funNumber < MAX_TIMERS) {
		fct[funNumber].divider = div;
		fct[funNumber].function_pointer = timerfkt;
		fct[funNumber].counter = 0;
		funNumber++;

	}

	return 0;
}

/*
 * Process next tick.
 * Must be called periodically with a frequency of TICKRATE_HZ
 * Return: 1 for success, 0 for failure
 */
void timer_tick(void) {

	for (int i = 0; i < funNumber; i++) {
		fct[i].counter++;      //timer is counting
		if (fct[i].counter == fct[i].divider) {
			fct[i].counter = 0;
			fct[i].function_pointer();
		}
	}

}


