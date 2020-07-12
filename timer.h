/*
 * timer.h
 *
 * Created: 5/7/2020 05:38:03
 *  Author: Hassan
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void timer_vid_set_isr_timer0_ctc (void (*callback_function) (void));
void timer_vid_set_isr_timer1a_ctc (void (*callback_function) (void));
void timer_vid_set_isr_timer1b_ctc (void (*callback_function) (void));
void timer_vid_set_isr_timer2_ctc (void (*callback_function) (void));
void timer_vid_init0_ctc (u16 prescalar, u8 top, u8 interrupt);
void timer_vid_init1_ctc (u16 prescalar, u16 top, u8 interrupt, u8 channel);
void timer_vid_init2_ctc (u16 prescalar, u8 top, u8 interrupt);




#endif /* TIMER_H_ */