#include "state.h"
#include "AlarmActuator.h"

void (*AA_state_ptr)();




void AA_init(void)
{
	//init alarm actuator
	Set_Alarm_actuator(TURN_OFF);
}

STATE_DECLARATION(AA_waiting)
{
	AA_state_id = AA_waiting_id;
}


STATE_DECLARATION(AA_AlarmOn)
{
	AA_state_id = AA_AlarmOn_id;
	Set_Alarm_actuator(TURN_ON);
}


STATE_DECLARATION(AA_AlarmOFF)
{
	AA_state_id = AA_AlarmOFF_id;
	Set_Alarm_actuator(TURN_OFF);
}


void StartAlarm()
{
	AA_state_ptr = STATE(AA_AlarmOn);
}


void StopAlarm()
{
	AA_state_ptr = STATE(AA_AlarmOFF);
}
