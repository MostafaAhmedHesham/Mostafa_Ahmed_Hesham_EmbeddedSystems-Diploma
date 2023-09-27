#ifndef ALARM_ACTUATOR_H
#define ALARM_ACTUATOR_H


#define TURN_ON 0
#define TURN_OFF 1



enum
{
	AA_waiting_id,
	AA_AlarmOn_id,
	AA_AlarmOFF_id
}AA_state_id;



extern void (*AA_state_ptr)();
void AA_init(void);
STATE_DECLARATION(AA_waiting);
STATE_DECLARATION(AA_AlarmOn);
STATE_DECLARATION(AA_AlarmOFF);









#endif
