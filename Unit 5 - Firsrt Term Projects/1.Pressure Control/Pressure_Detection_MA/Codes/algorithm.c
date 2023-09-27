#include "state.h"
#include "algorithm.h"

void (*algo_state_ptr)();

int Threshold = 20;


void Pressure_CMP(int Pval)
{
	algo_state_id = ALGO_CMP_id;
	if (Pval >= Threshold)
		High_pressure_detected();
	algo_state_ptr = STATE(Pressure_CMP);
}
