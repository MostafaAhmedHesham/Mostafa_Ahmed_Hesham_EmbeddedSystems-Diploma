#include "state.h"
#include "PressureSensor_Driver.h"
#include "algorithm.h"
#include "AlarmMonitor.h"
#include "AlarmActuator.h"



void setup()
{
	//Init block
	PS_init();
	AA_init();
	AM_init();
	//Set state pointer for each block
	PS_state_ptr = STATE(PS_reading);
	algo_state_ptr = STATE(Pressure_CMP);
	AM_state_ptr = STATE(AM_AlarmOFF);
	AA_state_ptr = STATE(AA_waiting);
}



int main (){
	GPIO_INITIALIZATION();
	setup();
	while (1)
	{
		//Implement your Design
		PS_state_ptr();
		AM_state_ptr();
		AA_state_ptr();

	}

}
