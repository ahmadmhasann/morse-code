/*
* to_morse.c
*
* Created: 7/14/2020 14:16:25
*  Author: Hassan
*/


#define F_CPU 8000000
#include <util/delay.h>
#include "types.h"
#include "dio.h"
#include "lcd.h"
#include "macros.h"
#include "keypad.h"
#include "to_morse.h"


u8 enteredKey;
u8 delayCounter = 0;
u8 lettersCounter = 0;
u8 letters[80] = {' '};
u8 lastKey = CLEAR_KEY;
u8 switchChar = 0;


u8 to_morse_u8_get_letter (u8 key) {
	/*
	* if less than 500ms passed and the last key pressed is the current key, switch the letters
	* delayCounter!= 0 indicates that the user pressed any button in the last 500ms
	*/
	if (delayCounter <= 100 && delayCounter!= 0 && lastKey == key) {
		switchChar = 1;
		switch(key) {
			delayCounter = 1;
			case 0: return letters[lettersCounter-1] == 'a'? 'b' : 'a' ;
			case 1: return letters[lettersCounter-1] == 'c'? 'd' : 'c' ;
			case 2: return letters[lettersCounter-1] == 'e'? 'f' : 'e' ;
			case 3: return letters[lettersCounter-1] == 'g'? 'h' : 'g' ;
			case 4: return letters[lettersCounter-1] == 'i'? 'j' : 'i' ;
			case 5: return letters[lettersCounter-1] == 'k'? 'l' : 'k' ;
			case 6: return letters[lettersCounter-1] == 'm'? 'n' : 'm' ;
			case 7: return letters[lettersCounter-1] == 'o'? 'p' : 'o' ;
			case 8: return letters[lettersCounter-1] == 'q'? 'r' : 'q' ;
			case 9: return letters[lettersCounter-1] == 's'? 't' : 's' ;
			case 10: return letters[lettersCounter-1] == 'u'? 'v' : 'u' ;
			case 11: return letters[lettersCounter-1] == 'w'? 'x' : 'w' ;
			case 15: return letters[lettersCounter-1] == 'y'? 'z' : 'y' ;
			default: return ' ';
		}
	}
	else {
		delayCounter = 1;
		switchChar = 0;
		switch(key) {
			case 0: return 'a';
			case 1: return 'c';
			case 2: return 'e';
			case 3: return 'g';
			case 4: return 'i';
			case 5: return 'k';
			case 6: return 'm';
			case 7: return 'o';
			case 8: return 'q';
			case 9: return 's';
			case 10: return 'u';
			case 11: return 'w';
			case 15: return 'y';
			default: return ' ';
		}
	}

}
void to_morse_check_keys (void) {
	keypad_vid_run();
	enteredKey = keyad_u8_get_number();
	/*
	* delayCounter = 0 if the user did not press any button for 500 ms
	* delayCounter is set to 1 when any button pressed in get letter function
	* delayCounter is incremented once every 5ms so delayCounter = 100 means 500ms passed without resetting delayCounter to one on button pressed
	*/
	if (delayCounter != 0) {
		delayCounter++;
		delayCounter = delayCounter>100? 0 : delayCounter;
	}
	if (enteredKey != KEYPAD_NO_NUMBER) {
		if (enteredKey == CLEAR_KEY) {
			lettersCounter = 0;
			lcd_vid_clear_screan();
		}
		else if (enteredKey == CONVERT_KEY) {
			to_morse_vid_convert_text();
		}
		else {
			u8 letter = to_morse_u8_get_letter(enteredKey);
			if (switchChar) {
				letters[lettersCounter - 1] = letter;
				lcd_vid_set_position(0, lettersCounter-1);
				lcd_vid_write_charachter(letter);
			}
			else {
				letters[lettersCounter] = letter;
				/*move to next line of LCD*/
				if (lettersCounter == 40) {
					lcd_vid_set_position(1, 0);
				}
				lcd_vid_write_charachter(letter);
				lettersCounter++;
			}
			lastKey = enteredKey;
		}
		
	}
}

void to_morse_vid_init (void) {
	dio_vid_set_pin_direction(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
}

void to_morse_run (void) {
	while (1) {
		to_morse_check_keys();
		_delay_ms(5);
	}
}

void to_morse_vid_convert_text (void) {
	u8 counter;
	for (counter = 0; counter < lettersCounter; counter++) {
		if (letters[counter] == ' ') to_morse_vid_display_space();
		else to_morse_vid_display_char(letters[counter]);
	}
}

void to_morse_vid_display_dot (void) {
	dio_vid_set_pin_value(BUZZER_PORT, BUZZER_PIN, PIN_HIGH);
	_delay_ms(ONE_UNIT_DELAY_MS);
	dio_vid_set_pin_value(BUZZER_PORT, BUZZER_PIN, PIn_LOW);
	_delay_ms(ONE_UNIT_DELAY_MS * 3);
}

void to_morse_vid_display_dash (void) {
	dio_vid_set_pin_value(BUZZER_PORT, BUZZER_PIN, PIN_HIGH);
	_delay_ms(ONE_UNIT_DELAY_MS * 3);
	dio_vid_set_pin_value(BUZZER_PORT, BUZZER_PIN, PIn_LOW);
	_delay_ms(ONE_UNIT_DELAY_MS * 3);
}
void to_morse_vid_display_space (void) {
	dio_vid_set_pin_value(BUZZER_PORT, BUZZER_PIN, PIN_HIGH);
	_delay_ms(ONE_UNIT_DELAY_MS * 7);
	dio_vid_set_pin_value(BUZZER_PORT, BUZZER_PIN, PIn_LOW);
	_delay_ms(ONE_UNIT_DELAY_MS * 3);
}

void to_morse_vid_display_char (u8 character) {
	s8 i, code, codeLength;
	switch (character) {
		case 'a':
		code = 0b01;
		codeLength = 2;
		break;
		case 'b':
		code = 0b1000;
		codeLength = 4;
		break;
		case 'c':
		code = 0b1010;
		codeLength = 4;
		break;
		case 'd':
		code = 0b100;
		codeLength = 3;
		break;
		case 'e':
		code = 0b0;
		codeLength = 1;
		break;
		case 'f':
		code = 0b0010;
		codeLength = 4;
		break;
		case 'g':
		code = 0b110;
		codeLength = 3;
		break;
		case 'h':
		code = 0b0000;
		codeLength = 4;
		break;
		case 'i':
		code = 0b00;
		codeLength = 2;
		break;
		case 'j':
		code = 0b0111;
		codeLength = 4;
		break;
		case 'k':
		code = 0b101;
		codeLength = 3;
		break;
		case 'l':
		code = 0b0100;
		codeLength = 4;
		break;
		case 'm':
		code = 0b11;
		codeLength = 2;
		break;
		case 'n':
		code = 0b10;
		codeLength = 2;
		break;
		case 'o':
		code = 0b111;
		codeLength = 3;
		break;
		case 'p':
		code = 0b0110;
		codeLength = 4;
		break;
		case 'q':
		code = 0b1101;
		codeLength = 4;
		break;
		case 'r':
		code = 0b010;
		codeLength = 3;
		break;
		case 's':
		code = 0b000;
		codeLength = 3;
		break;
		case 't':
		code = 0b1;
		codeLength = 1;
		break;
		case 'u':
		code = 0b001;
		codeLength = 3;
		break;
		case 'v':
		code = 0b0001;
		codeLength = 4;
		break;
		case 'w':
		code = 0b011;
		codeLength = 3;
		break;
		case 'x':
		code = 0b1001;
		codeLength = 4;
		break;
		case 'y':
		code = 0b1011;
		codeLength = 4;
		break;
		case 'z':
		code = 0b1100;
		codeLength = 4;
		break;
		default:
		code = 0b0;
		codeLength = 1;
		break;
	}
	for (i=codeLength-1; i>=0; i--) {
		if (getBit(code, i) == 0) to_morse_vid_display_dot();
		else to_morse_vid_display_dash();
	}
}