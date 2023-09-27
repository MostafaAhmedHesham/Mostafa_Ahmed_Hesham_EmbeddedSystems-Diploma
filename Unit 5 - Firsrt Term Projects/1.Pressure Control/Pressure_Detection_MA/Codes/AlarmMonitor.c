#include "state.h"
#include "AlarmMonitor.h"

void (*AM_state_ptr)();

void AM_init()
{
	//init Alarm Monitor
}


STATE_DECLARATION(AM_AlarmOFF)
{
	AM_state_id = AM_AlarmOFF_id;
}


STATE_DECLARATION(AM_AlarmOn)
{
	AM_state_id = AM_AlarmOn_id;

	StartAlarm();
	AM_state_ptr = STATE(AM_waiting);
}


STATE_DECLARATION(AM_waiting)
{
	AM_state_id = AM_waiting_id;
	Delay(6000);
	StopAlarm();
	AM_state_ptr = STATE(AM_AlarmOFF);

}


void High_pressure_detected()
{
	AM_state_ptr = STATE(AM_AlarmOn);
}


