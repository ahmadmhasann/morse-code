/*
* dio.c
*
*	Created on: Aug 17, 2019
*   Author: Ahmed Hassan
*/

#include <avr/io.h>
#include "types.h"
#include "macros.h"
#include "dio.h"

void dio_vid_set_port_direction (u8 portNumber, u8 direction) {
	switch (portNumber) {
		case A:
			DDRA = direction;
			break;
		case B:
			DDRB = direction;
			break;
		case C:
			DDRC = direction;
			break;
		case D:
			DDRD = direction;
			break;
		default:
			break;
	}
}


void dio_vid_set_port_value (u8 portNumber, u8 value) {
	switch (portNumber) {
		case A:
			PORTA = value;
			break;
		case B:
			PORTB = value;
			break;
		case C:
			PORTC = value;
			break;
		case D:
			PORTD = value;
			break;
		default:
			break;
	}
}

u8 dio_u8_read_port_value (u8 portNumber) {
	switch (portNumber) {
		case A:
			return PINA;
			break;
		case B:
			return PINB;
			break;
		case C:
			return PINC;
			break;
		case D:
			return PIND;
			break;
		default:
			return 0;
			break;
	}
}


u8 dio_u8_read_pin_value (u8 portNumber, u8 index) {
	u8 port = dio_u8_read_port_value(portNumber);
	return getBit(port, index);
}

void dio_vid_set_pin_value (u8 portNumber, u8 index, u8 value) {
	switch (portNumber) {
		case A:
			if (value == 1)
				setBit(PORTA, index);
			else if (value == 0)
				clrBit(PORTA, index);
			break;
		case B:
			if (value == 1)
				setBit(PORTB, index);
			else if (value == 0)
				clrBit(PORTB, index);
			break;
		case C:
			if (value == 1)
				setBit(PORTC, index);
			else if (value == 0)
				clrBit(PORTC, index);
			break;
		case D:
			if (value == 1)
				setBit(PORTD, index);
			else if (value == 0)
				clrBit(PORTD, index);
			break;
		default:
			break;
	}
}


void dio_vid_set_pin_direction (u8 portNumber, u8 index, u8 direction) {
	switch (portNumber) {
		case A:
			if (direction == 1)
			setBit(DDRA, index);
			else if (direction == 0)
			clrBit(DDRA, index);
			break;
		case B:
			if (direction == 1)
			setBit(DDRB, index);
			else if (direction == 0)
			clrBit(DDRB, index);
			break;
		case C:
			if (direction == 1)
				setBit(DDRC, index);
			else if (direction == 0)
				clrBit(DDRC, index);
			break;
		case D:
			if (direction == 1)
				setBit(DDRD, index);
			else if (direction == 0)
				clrBit(DDRD, index);
			break;
		default:
			break;
	}
}

void dio_vid_toggle_pin_value (u8 portNumber, u8 index) {
	switch (portNumber) {
		case A:
			toggleBit(PORTA, index);
			break;
		case B:
			toggleBit(PORTB, index);
			break;
		case C:
			toggleBit(PORTC, index);
			break;
		case D:
			toggleBit(PORTD, index);
			break;
		default:
			break;

	}
}