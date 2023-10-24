/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: AEMYS
 */

#include <Keypad.h>
#include <LCD.h>

int main(void)
{
	LCD_init();
	KEYPAD_init();
	LCD_write_char('A');
	LCD_write_string("ABCDE");
	LCD_GOTO_position(SECOND_LINE, 7);
	LCD_write_string("ABCDE");
	uint8_t key_char;
	while(1)
	{
		key_char = KEYPAD_get_charcter();
		switch (key_char)
		{
			case 'a':
				//no key pressed
				break;
			case 'c':
				LCD_clear_screen();
				//make counter @ LCD_write_char to be 1
				break;
			default:
				LCD_write_char(key_char);
				break;
		}
	}
	return 0;
}

///* Make delays minimum as possible */
