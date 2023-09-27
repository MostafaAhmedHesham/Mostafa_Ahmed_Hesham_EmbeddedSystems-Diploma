#ifndef STATE_H
#define STATE_H

#include "driver.h"
#include "stdio.h"
#include "platform_types.h"


#define STATE_DECLARATION(state_name) void state_name(void)
#define STATE(state_name) state_name



void High_pressure_detected();
void StartAlarm();
void StopAlarm();

#endif
