/*
* from_morse.c
*
* Created: 7/12/2020 16:32:08
*  Author: Hassan
*/
#define F_CPU 8000000
#include <util/delay.h>
#include "types.h"
#include "dio.h"
#include "lcd.h"
#include "from_morse.h"
#include "macros.h"
u32 oneUnitCounter = 0; /*dot*/
u32 threeUnitCounter = 0; /*dash*/
u32 sevenUnitCounter = 0; /*space*/

void from_morse_vid_init (void) {
	/*Input and pull up*/
	dio_vid_set_pin_direction(TOUCH_SENSOR_PORT, TOUCH_SENSOR_PIN, PIN_INPUT);
	dio_vid_set_pin_value(TOUCH_SENSOR_PORT, TOUCH_SENSOR_PIN, PIN_HIGH);
	/*wait until success calibrate*/
	while (1) {
		if (from_morse_vid_calibrate() == CALIBRATE_DONE) {
			break;
		}
	}	
}

void from_morse_vid_run (void) {
	u8 charCounter = 0;
	lcd_vid_clear_screan();
	while (1) {
		/*get char from user and print on LCD*/
		lcd_vid_write_charachter(from_morse_u8_get_letter());
		charCounter++;
		/*if first line of LCD is full, move to second line*/
		if (charCounter == 40)
			lcd_vid_set_position(1,0);
		/*if LCD is full wait 2 seconds and clear*/
		if (charCounter == 80) {
			_delay_ms(2000);
			lcd_vid_clear_screan();
			charCounter = 0;
		}
	}
}

u8 from_morse_vid_calibrate (void) {
	u8 i, one_three_seven;
	u32 counter = 0;
	/*get time of each unit from user*/
	lcd_vid_clear_screan();
	for (one_three_seven = 1; one_three_seven<8; one_three_seven = one_three_seven*2+1) {
		for (i=1; i<4; i++) {
			lcd_vid_set_position(0,0);
			switch (one_three_seven) {
				case 1:
				lcd_vid_write_string((u8*)"Hold the sensor to set dot (.) time");
				break;
				case 3:
				lcd_vid_write_string((u8*)"Hold the sensor to set dash (-) time");
				break;
				case 7:
				lcd_vid_write_string((u8*)"Hold the sensor to set space (/) time");
				break;
				default:
				break;
			}
			lcd_vid_set_position(1,0);
			lcd_vid_write_number(i);
			lcd_vid_write_string((u8*)" of 3");
			while (1)
			{
				if (dio_u8_read_pin_value(TOUCH_SENSOR_PORT, TOUCH_SENSOR_PIN) == 0)
				counter++;
				else if (counter!=0)
				break;
			}
			switch (one_three_seven) {
				case 1:
				oneUnitCounter += counter;
				break;
				case 3:
				threeUnitCounter += counter;
				break;
				case 7:
				sevenUnitCounter += counter;
				break;
				default:
				break;
			}
			counter = 0;
		}
		lcd_vid_clear_screan();
		/*get average value of three trials*/
		switch (one_three_seven) {
			case 1:
			oneUnitCounter /= 3;
			lcd_vid_write_string((u8*)"dot (.) time set successfully");
			break;
			case 3:
			threeUnitCounter /= 3;
			lcd_vid_write_string((u8*)"dash (-) time set successfully");
			break;
			case 7:
			sevenUnitCounter /= 3;
			lcd_vid_write_string((u8*)"space (/) time set successfully");
			break;
			default:
			break;
		}
		_delay_ms(2000);
		lcd_vid_clear_screan();
	}
	if (oneUnitCounter<threeUnitCounter && threeUnitCounter<sevenUnitCounter) return CALIBRATE_DONE;
	else {
		lcd_vid_write_string((u8*)"one should be less than three and seven");
		lcd_vid_set_position(1,0);
		lcd_vid_write_string((u8*)"Try again");
		_delay_ms(3000);
		lcd_vid_clear_screan();
		return CALIBRATE_FAIlED;
	}
}

u8 from_morse_u8_get_letter (void) {
	u32 pressCounter = 0;
	u32 releaseCounter = 0;
	u8 startedPressing = 0;
	u8 letterCode = 1;
	while (1) {
		/*the user started pressing touch sensor*/
		if (dio_u8_read_pin_value(TOUCH_SENSOR_PORT, TOUCH_SENSOR_PIN) == 0) {
			startedPressing = 1;
			pressCounter++;
		}
		/*the user released touch sensor after pressing*/
		else if (startedPressing) {
			/*get the number of units*/
			u8 units = from_morse_get_closer_units(pressCounter);
			/*
			* the last bit of code is 1 to indicate its length
			* 1 unit is represented by low bit
			* 3 units is represented by high bit
			* for example
			* letter a (.-) will be 00000101
			* letter g (--.) will be 00001110
			* letter h (....) will be 00010000
			*/
			if (units == 7)
				return ' ';
			else if (units == 3)
				letterCode = (letterCode<<1) + 1;
			else if (units == 1)
				letterCode = letterCode<<1;
			pressCounter = 0;
			startedPressing = 0;
		}
		else {
			/*check that at least any touch happened before return*/
			if (letterCode != 1) {
				releaseCounter++;
				/*check that 3 units is passed without touching which is the space between letters*/
				if (releaseCounter > threeUnitCounter) {
					return from_morse_u8_convert_code(letterCode);
				}
			}
	}
}
}

u8 from_morse_get_closer_units (u32 number) {
	if ((number>=sevenUnitCounter) ||
		((number>= threeUnitCounter) && (number-threeUnitCounter > sevenUnitCounter - number))) 
		return 7;
	if ((number>=threeUnitCounter) ||
	((number>= oneUnitCounter) && (number-oneUnitCounter > threeUnitCounter - number))) 
		return 3;
	return 1;
}

u8 from_morse_u8_convert_code (u8 code) {
	u8 length = 8;
	for (u8 i=7; i>=0; i--) {
		length--;
		if (getBit(code, i) == 1)
			break;
	}
	if (length == 1) {
		if ((code & 0b00000001) == 0b00000001) return 't';
		if ((code & 0b00000001) == 0b00000000) return 'e';
	}
	if (length == 2) {
		if ((code & 0b00000011) == 0b00000001) return 'a';
		if ((code & 0b00000011) == 0b00000000) return 'i';
		if ((code & 0b00000011) == 0b00000010) return 'n';
		if ((code & 0b00000011) == 0b00000011) return 'm';
	}
	if (length == 3) {
		if ((code & 0b00000111) == 0b00000100) return 'd';
		if ((code & 0b00000111) == 0b00000110) return 'g';
		if ((code & 0b00000111) == 0b00000101) return 'k';
		if ((code & 0b00000111) == 0b00000111) return 'o';
		if ((code & 0b00000111) == 0b00000010) return 'r';
		if ((code & 0b00000111) == 0b00000000) return 's';
		if ((code & 0b00000111) == 0b00000001) return 'u';
		if ((code & 0b00000111) == 0b00000011) return 'w';
	}
	if (length == 4) {
		if ((code & 0b00001111) == 0b00001000) return 'b';
		if ((code & 0b00001111) == 0b00001010) return 'c';
		if ((code & 0b00001111) == 0b00000010) return 'f';
		if ((code & 0b00001111) == 0b00000000) return 'h';
		if ((code & 0b00001111) == 0b00000111) return 'j';
		if ((code & 0b00001111) == 0b00000100) return 'l';
		if ((code & 0b00001111) == 0b00000110) return 'p';
		if ((code & 0b00001111) == 0b00001101) return 'q';
		if ((code & 0b00001111) == 0b00000001) return 'v';
		if ((code & 0b00001111) == 0b00001001) return 'x';
		if ((code & 0b00001111) == 0b00001011) return 'y';
		if ((code & 0b00001111) == 0b00001100) return 'z';
	}
	if (length == 5) {
		if ((code & 0b00011111) == 0b00001111) return '1';
		if ((code & 0b00011111) == 0b00000111) return '2';
		if ((code & 0b00011111) == 0b00000011) return '3';
		if ((code & 0b00011111) == 0b00000001) return '4';
		if ((code & 0b00011111) == 0b00000000) return '5';
		if ((code & 0b00011111) == 0b00010000) return '6';
		if ((code & 0b00011111) == 0b00011000) return '7';
		if ((code & 0b00011111) == 0b00011100) return '8';
		if ((code & 0b00011111) == 0b00011110) return '9';
		if ((code & 0b00011111) == 0b00011111) return '0';
	}
	return ' ';	
}
