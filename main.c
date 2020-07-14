/*
* morse-code.c
*
* Created: 7/8/2020 23:44:19
* Author : Hassan
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"
#include "types.h"
#include "dio.h"
#include "lcd.h"
#include "keypad.h"
#include "scheduler.h"
#include "from_morse.h"
#include "mode.h"
#include "to_morse.h"

int main(void)
{
	u8 deviceMode;
	lcd_vid_init();
	keypad_vid_init();
	deviceMode = mode_u8_get_mode();
	if (deviceMode == FROM_MORSE_MODE) {
			from_morse_vid_init();
			from_morse_vid_run();
	}
	else if (deviceMode == TO_MORSE_MODE) {
		lcd_vid_clear_screan();
		to_morse_vid_init();
		to_morse_run();
	}
	

	
}

