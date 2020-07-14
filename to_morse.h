/*
 * to_morse.h
 *
 * Created: 7/14/2020 14:17:05
 *  Author: Hassan
 */ 


#ifndef TO_MORSE_H_
#define TO_MORSE_H_

#define CONVERT_KEY 12
#define CLEAR_KEY 14
#define BUZZER_PORT D
#define BUZZER_PIN 4
#define ONE_UNIT_DELAY_MS 100

void to_morse_vid_init (void);
void to_morse_run (void);
void to_morse_check_keys (void);
u8 to_morse_u8_get_letter (u8 key);
void to_morse_vid_convert_text (void);
void to_morse_vid_display_dot (void);
void to_morse_vid_display_dash (void);
void to_morse_vid_display_space (void);
void to_morse_vid_display_char (u8 character);
#endif /* TO_MORSE_H_ */