/*
 * dc_motor.c
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */
#include "dc_motor.h"

int DC_speed;
void (*DC_state_ptr)();



void DC_init()
{
	//init PWM driver
	printf("___________________DC____________init________________\n");
}


STATE_define(DC_idle)
{
	//state name
	DC_state_id = dc_idle;

	printf("DC_idle state: Speed = %d\n\n",DC_speed);

}

STATE_define(DC_busy)
{
	//state name
	DC_state_id = dc_busy;

	//state action
	//call PWM to make motor speed = DC_speed

	DC_state_ptr = STATE(DC_idle);
	printf("DC_busy state: Speed = %d\n\n",DC_speed);
}

void DC_motor(int speed)
{
	int prev_speed = DC_speed;
	DC_speed = speed;

	/*Optimization: if there is no change in speed so i don't have to write on motor with*/
	if (prev_speed == DC_speed)
		DC_state_ptr = STATE(DC_idle);
	else
		DC_state_ptr = STATE(DC_busy);

	printf("CA---------Speed=%d----------->DC\n",DC_speed);
}
