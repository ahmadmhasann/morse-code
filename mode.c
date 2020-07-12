/*
* mode.c
*
* Created: 7/12/2020 18:27:22
*  Author: Hassan
*/
#define F_CPU 8000000
#include <util/delay.h>
#include "types.h"
#include "dio.h"
#include "lcd.h"
#include "mode.h"
#include "macros.h"
#include "keypad.h"
u8 mode_u8_get_mode (void) {
	u8 key;
	lcd_vid_clear_screan();
	lcd_vid_write_string((u8*)"Press 1 to translate to Morse");
	lcd_vid_set_position(1,0);
	lcd_vid_write_string((u8*)"Press 2 to translate from Morse");
	while (1)
	{
		keypad_vid_run();
		key = keyad_u8_get_number();
		if (key != KEYPAD_NO_NUMBER) {
			if (key == 9)
				return TO_MORSE_MODE;
			else if (key == 8)
				return FROM_MORSE_MODE;
		}
	}
}