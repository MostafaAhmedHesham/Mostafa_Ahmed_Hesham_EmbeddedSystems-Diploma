#ifndef PRESSURE_SENSOR_DRIVER_H
#define PRESSURE_SENSOR_DRIVER_H




enum
{
	PS_reading_id,
	PS_waiting_id
}PressureSensor_state_id;


void PS_init();
STATE_DECLARATION(PS_reading);
STATE_DECLARATION(PS_waiting);
void Pressure_CMP(int Pval);
void (*PS_state_ptr)();

#endif
