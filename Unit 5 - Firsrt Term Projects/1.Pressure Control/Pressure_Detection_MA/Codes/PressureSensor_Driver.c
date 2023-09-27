#include "state.h"
#include "PressureSensor_Driver.h"



int Pval;
void (*PS_state_ptr)();

void PS_init()
{
	//init Pressure sensor driver
}

STATE_DECLARATION(PS_reading)
{
	PressureSensor_state_id = PS_reading_id;

	Pval = getPressureVal(); 		//Read Pressure value
	Pressure_CMP(Pval); 			//Send Pressure value to algorithm
	PS_state_ptr = STATE(PS_waiting);	//Switch to waiting state
}

STATE_DECLARATION(PS_waiting)
{
	PressureSensor_state_id = PS_waiting_id;
	Delay(1000);
	PS_state_ptr = STATE(PS_reading);
}



