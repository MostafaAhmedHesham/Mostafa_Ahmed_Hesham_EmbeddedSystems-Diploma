#include "stdio.h"
#include "avr/io.h"


#include "UART.h"
#include "LCD.h"

uint16_t Buffer;
void Mostafa_CallBack(void);

int main()
{
	LCD_init();
	USART_Config config_uart;

	config_uart.BaudRate = USART_BaudRate_19200;
	config_uart.DataBits = USART_DataBits_7;
	config_uart.Interrupt = USART_Interrupt_RXCIE;
	config_uart.MODE = USART_MODE_TX_RX;
	config_uart.Parity = USART_Parity_EVEN;
	config_uart.StopBits = USART_StopBits_1;
	config_uart.USART_IRQ_Func = Mostafa_CallBack;
	MCAL_UART_Init(&config_uart);


	while (1)
	{

	}
	return 0;
}

void Mostafa_CallBack(void)
{
	MCAL_UART_ReceiveData(&Buffer, USART_Polling_Disable);
	MCAL_UART_SendData(&Buffer, USART_Polling_Enable);
	LCD_write_char(Buffer);
}
