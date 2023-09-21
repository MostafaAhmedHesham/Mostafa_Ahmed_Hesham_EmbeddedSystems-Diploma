/*
 * collision_avoidance.h
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */

#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_

#include "state.h"


enum {
	ca_waiting,
	ca_driving
}CA_state_id;


extern void (*CA_state_ptr)();
STATE_define(CA_waiting);
STATE_define(CA_driving);



#endif /* COLLISION_AVOIDANCE_H_ */
