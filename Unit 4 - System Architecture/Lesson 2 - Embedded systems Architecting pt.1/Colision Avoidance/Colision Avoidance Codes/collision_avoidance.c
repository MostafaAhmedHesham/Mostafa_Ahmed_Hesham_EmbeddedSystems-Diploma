/*
 * collision_avoidance.c
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */

#include "collision_avoidance.h"

int CA_distance, CA_speed, CA_threshold = 50;
void (*CA_state_ptr)();

void US_set_distance(int distance)
{
	CA_distance = distance;
	(CA_distance <= CA_threshold)? (CA_state_ptr = STATE(CA_waiting)) : (CA_state_ptr = STATE(CA_driving));
	printf("US---------Distance=%d----------->CA\n",CA_distance);
}

STATE_define(CA_waiting)
{
	//state name
	CA_state_id = ca_waiting;
	printf("Waiting state: Distance = %d Speed = %d\n",CA_distance,CA_speed);

	//state action
	CA_speed = 0;
	DC_motor(CA_speed);
}


STATE_define(CA_driving)
{
	//state name
	CA_state_id = ca_driving;
	printf("Driving state: Distance = %d Speed = %d\n",CA_distance,CA_speed);

	//state action
	CA_speed = 30;
	DC_motor(CA_speed);
}
