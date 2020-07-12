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

#define PORT_OUTPUT 0xFF
#define PORT_INPUT 0x00

#define PIN_OUTPUT 0x01
#define PIN_INPUT 0x00

#define PORT_HIGH 0xFF
#define PORT_LOW 0x00

#define PIN_HIGH 0x01
#define PIn_LOW 0x00

u8 dio_u8_read_port_value (u8 portNumber);
u8 dio_u8_read_pin_value (u8 portNumber, u8 index);
void dio_vid_set_port_direction (u8 portNumber, u8 direction);
void dio_vid_set_port_value (u8 portNumber, u8 value);
void dio_vid_set_pin_direction (u8 portNumber, u8 index, u8 direction);
void dio_vid_set_pin_value (u8 portNumber, u8 index, u8 value);
void dio_vid_toggle_pin_value (u8 portNumber, u8 index);

#endif /* DIO_H_ */


