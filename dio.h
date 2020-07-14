/*
 * dio.h
 *
 *  Created on: Aug 17, 2019
 *      Author: Ahmed Hassan
 */

#ifndef DIO_H_
#define DIO_H_

enum {
	A,
	B,
	C,
	D
};

#define OUTPUT_PORT 0xFF
#define INPUT_PORT 0x00

#define OUTPUT_PIN 0x01
#define INPUT_PIN 0x00

#define HIGH_PORT 0xFF
#define LOW_PORT 0x00

#define HIGH_PIN 0x01
#define LOW_PIN 0x00

u8 dio_u8_read_port_value (u8 portNumber);
u8 dio_u8_read_pin_value (u8 portNumber, u8 index);
void dio_vid_set_port_direction (u8 portNumber, u8 direction);
void dio_vid_set_port_value (u8 portNumber, u8 value);
void dio_vid_set_pin_direction (u8 portNumber, u8 index, u8 direction);
void dio_vid_set_pin_value (u8 portNumber, u8 index, u8 value);
void dio_vid_toggle_pin_value (u8 portNumber, u8 index);

#endif /* DIO_H_ */


