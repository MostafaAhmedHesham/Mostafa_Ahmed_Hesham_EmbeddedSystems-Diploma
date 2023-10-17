/*
 * main.c
 *
 *  Created on: Oct 16, 2023
 *      Author: AEMYS
 */
#include "stdint.h"
//#define F_CPU 1000000UL

typedef volatile unsigned int vuint32_t;


#define BASE 	0x20
#define PORTD 	*(vuint32_t *)(BASE + 0x12)
#define DDRD	*(vuint32_t *)(BASE + 0x11)
#define PIND	*(vuint32_t *)(BASE + 0x10)

#define LED1 	(0b001<<5)
#define LED2 	(0b010<<5)
#define LED3	(0b100<<5)
#define BUZZER 	(0b0001<<4)
#define RESET_PORTD (PORTD = 0)


void GPIO_init(void);

void my_delay(uint8_t delay_cycles);

/** LEDS and Buzzer turns on/off sequentially */
void Sequential_LEDS(void);

/** Each Button Press Turn ON one led until
  turn ON all 3 LEDs then turn ON Buzzer and
  one more press to reset system  */
void Button_LEDS_BUZZER(void);


int main()
{
	GPIO_init();

	//Sequential_LEDS();
	Button_LEDS_BUZZER();


	return 0;
}


void GPIO_init(void)
{
	// Set PORTD Pin 4, 5, 6, 7 to be output
	DDRD |= (0b1111 << 4);

	// Set PORTD Pin 0 to be input
	DDRD &= ~(1 << 0);
}

void my_delay(uint8_t delay_cycles)
{
	for(uint8_t i = 0 ; i < delay_cycles ; i++)
		for(uint8_t j = 0 ; j < 255 ; j++);
}


void Button_LEDS_BUZZER(void)
{
	uint8_t flag = 0;
	while (1)
	{
		if (	((PIND & (1 << 0)) >> 0) == 1 && flag == 0)
		{
			PORTD |= LED1;
			flag++;
			while((PIND & (1 << 0)) >> 0);
		}

		if (	((PIND & (1 << 0)) >> 0) == 1 && flag == 1)
		{
			PORTD |= LED1;
			PORTD |= LED2;
			flag++;
			while((PIND & (1 << 0)) >> 0);
		}

		if (	((PIND & (1 << 0)) >> 0) == 1 && flag == 2)
		{
			PORTD |= LED1;
			PORTD |= LED2;
			PORTD |= LED3;
			flag++;
			while((PIND & (1 << 0)) >> 0);
		}

		if (	((PIND & (1 << 0)) >> 0) == 1 && flag == 3)
		{
			RESET_PORTD;
			PORTD |= BUZZER;
			flag++;
			while((PIND & (1 << 0)) >> 0);
		}
		if (	((PIND & (1 << 0)) >> 0) == 1 && flag == 4)
		{
			flag = 0;
			RESET_PORTD;
			while((PIND & (1 << 0)) >> 0);
		}
	}
}

void Sequential_LEDS(void)
{
	while(1)
	{
		PORTD |= LED1;
		my_delay(1);
		RESET_PORTD;

		PORTD |= LED2;
		my_delay(1);
		RESET_PORTD;

		PORTD |= LED3;
		my_delay(1);
		RESET_PORTD;

		PORTD |= BUZZER;
		my_delay(5);
		RESET_PORTD;
	}
}
