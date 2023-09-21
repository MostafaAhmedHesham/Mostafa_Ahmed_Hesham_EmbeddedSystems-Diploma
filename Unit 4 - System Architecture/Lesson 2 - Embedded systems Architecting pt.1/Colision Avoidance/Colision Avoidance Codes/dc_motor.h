/*
 * dc_motor.h
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "state.h"

enum{
	dc_idle,
	dc_busy
}DC_state_id;


extern void (*DC_state_ptr)();
void DC_init();
STATE_define(DC_idle);
STATE_define(DC_busy);
#endif /* DC_MOTOR_H_ */
