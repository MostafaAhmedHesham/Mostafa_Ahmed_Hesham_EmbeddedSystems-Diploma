/*
 * main.c
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */

#include "collision_avoidance.h"
#include "dc_motor.h"
#include "us_sensor.h"



void setup()
{
	//init all drivers
	//init IRQ......
	//init HAL US_driver DC_driver
	//Init block
	US_init();
	DC_init();
	//Set state pointer for each block
	US_state_ptr = STATE(US_busy);
	CA_state_ptr = STATE(CA_waiting);
	DC_state_ptr = STATE(DC_idle);
}

int main()
{
	volatile int d;
	setup();
	while (1)
	{
		//call state for each block
		US_state_ptr();
		CA_state_ptr();
		DC_state_ptr();
		for(d = 0 ; d <= 1000 ; d++);
	}
	return 0;
}
