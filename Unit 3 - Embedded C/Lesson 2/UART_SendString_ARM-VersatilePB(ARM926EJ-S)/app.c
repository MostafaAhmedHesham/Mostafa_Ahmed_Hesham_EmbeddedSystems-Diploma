#include "uart.h"

unsigned char buffer[100] = "Learn in depth <Mostafa Ahmed Hesham>";
unsigned char const buffer2[100] = ".rodata section";

void main()
{
	uart_send_string(buffer);
}