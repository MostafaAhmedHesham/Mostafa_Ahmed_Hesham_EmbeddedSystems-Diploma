#ifndef ALARM_MONITOR_H
#define ALARM_MONITOR_H









enum
{
	AM_AlarmOFF_id,
	AM_AlarmOn_id,
	AM_waiting_id
}AM_state_id;

extern void (*AM_state_ptr)();
void AM_init();
STATE_DECLARATION(AM_AlarmOFF);
STATE_DECLARATION(AM_AlarmOn);
STATE_DECLARATION(AM_waiting);







#endif
