/*
 * us_sensor.h
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */

#ifndef US_SENSOR_H_
#define US_SENSOR_H_


#include "state.h"

enum{
	us_busy
}US_state_id;


extern void (*US_state_ptr)();
void US_init();
STATE_define(US_busy);
int US_Get_distance_random(int l, int r, int count);

#endif /* US_SENSOR_H_ */
