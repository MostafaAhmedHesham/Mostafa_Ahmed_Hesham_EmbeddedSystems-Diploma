/*
 * state.h
 *
 *  Created on: Sep 19, 2023
 *      Author: AEMYS
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"

#define STATE_define(_stateFunc_) void ST_##_stateFunc_() //## for concatenate to resolve symbol _stateFunc_
#define STATE(_stateFunc_) ST_##_stateFunc_



//States Connections
void US_set_distance(int distance);
void DC_motor(int speed);

#endif /* STATE_H_ */
