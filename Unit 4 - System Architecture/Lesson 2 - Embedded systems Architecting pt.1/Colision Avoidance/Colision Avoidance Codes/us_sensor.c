/*
 * us_sensor.c
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */

#include "us_sensor.h"

void (*US_state_ptr)();
int US_distance;

void US_init()
{
	//init us driver
	printf("___________________US____________init________________\n");

}

STATE_define(US_busy)
{
	US_state_id = us_busy;

	US_distance = US_Get_distance_random(45,55,1);
	US_set_distance(US_distance);

	US_state_ptr = STATE(US_busy);
}

int US_Get_distance_random(int l, int r, int count)
{
	int rand_num;
	for(int i = 0 ; i < count ; i++)
		rand_num = ( rand() % (r-l+1) ) + l;
	return rand_num;
}
