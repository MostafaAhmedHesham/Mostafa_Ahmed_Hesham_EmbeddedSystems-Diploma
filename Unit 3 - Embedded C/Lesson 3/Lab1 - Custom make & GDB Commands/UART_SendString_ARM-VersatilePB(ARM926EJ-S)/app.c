#include "uart.h"

unsigned char buffer[100] = "Learn in depth <Mostafa Ahmed Hesham>";

void main()
{
	uart_send_string(buffer);
}