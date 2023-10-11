/*
 * main.c
 *
 *  Created on: Oct 11, 2023
 *      Author: AEMYS
 */

#define F_CPU 1000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

typedef volatile unsigned int vuint32_t;


#define BASE 	0x20
#define PORTD 	*(vuint32_t *)(BASE + 0x12)
#define DDRD	*(vuint32_t *)(BASE + 0x11)
#define DDRB	*(vuint32_t *)(BASE + 0x17)

#define MCUCSR	*(vuint32_t *)(BASE + 0x34)
#define MCUCR	*(vuint32_t *)(BASE + 0x35)
#define GIFR	*(vuint32_t *)(BASE + 0x3A)
#define GICR	*(vuint32_t *)(BASE + 0x3B)
#define SREG	*(vuint32_t *)(BASE + 0x3F)

ISR(INT0_vect)
{
	//Toggle LED
	PORTD |= (1 << 5);
	_delay_ms(1000);


	//Clear General Interrupt Flag Register "W1C"
	GIFR |= (1 << 6);
}

ISR(INT1_vect)
{
	//Toggle LED
	PORTD |= (1 << 6);
	_delay_ms(1000);

	//Clear General Interrupt Flag Register "W1C"
	GIFR |= (1 << 7);
}

ISR(INT2_vect)
{
	//Toggle LED
	PORTD |= (1 << 7);
	_delay_ms(1000);

	//Clear General Interrupt Flag Register "W1C"
	GIFR |= (1 << 5);
}


void IO_init(void)
{
	/**
		LEDS
	*///Output Direction for PortD Pin5,6,7 (LED)
	DDRD |= (0b111 << 5);


	/**
		Switches
	*///Direction of PortD Pin2/Pin3 (Switch 1/2) INT0/INT1
	DDRD &= ~(1 << 2);
	DDRD &= ~(1 << 3);
	//Direction of PortB Pin2 (Switch 3) INT2
	DDRB &= ~(1 << 2);
}

void EXTI_init(void)
{
	//MCU Control Register ISC 01 = 1 , ISC 00 = 1 (Any Logical Change)INT0
	MCUCR |= (0b01 << 0);

	//MCU Control Register ISC 11 = 1 , ISC 10 = 1 (rising edge) INT1
	MCUCR |= (0b11 << 2);

	//MCU Control State Register ISC 2 (falling edge) INT2
	MCUCSR &= ~(1 << 6);

	//Enable General Interrupt Control Register EXTI0, EXTI1, EXTI2
	GICR |= (0b111 << 5);

	//Global Interrupt Enable
	SREG |= (1 << 7);
	//sei();
}

int main(void)
{
	IO_init();
	EXTI_init();
	while (1)
	{
		//Turn Off Leds
		PORTD &= (0b000 << 5);
	}
	return 0;
}
