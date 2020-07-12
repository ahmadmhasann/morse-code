/*
 * from-morse.h
 *
 * Created: 7/12/2020 16:39:03
 *  Author: Hassan
 */ 


#ifndef FROM_MORSE_H_
#define FROM_MORSE_H_

#define CALIBRATE_DONE 1
#define CALIBRATE_FAIlED 0
#define TOUCH_SENSOR_PORT D
#define TOUCH_SENSOR_PIN 3
void from_morse_vid_init (void);
u8 from_morse_vid_calibrate (void);
u8 from_morse_u8_convert_code (u8 code);
u8 from_morse_u8_get_letter (void);
u8 from_morse_get_closer_units (u32 number);
void from_morse_vid_run (void);

#endif /* CALIBRATE_H_ */