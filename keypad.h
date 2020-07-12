/*
 * KeyPad.h
 *
 *  Created on: Aug 30, 2019
 *      Author: Ahmed Hassan
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPAD_NO_NUMBER 16

void keypad_vid_init (void);
u8 keypad_u8_get_button_status (u8 button);
void keypad_vid_run (void);
u8 keyad_u8_get_number(void);


#endif /* KEYPAD_H_ */
