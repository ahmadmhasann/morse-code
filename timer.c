/*
* timer.c
*
* Created: 5/7/2020 03:58:09
*  Author: Hassan
*/
#include <avr/io.h>
#include "macros.h"
#include "types.h"
#define __INTR_ATTRS used, externally_visible



void(*timer0_ctc_isr)(void);
void(*timer1a_ctc_isr)(void);
void(*timer1b_ctc_isr)(void);
void(*timer2_ctc_isr)(void);
void timer_vid_set_isr_timer0_ctc (void (*callback_function) (void))
{
	timer0_ctc_isr=callback_function;
}
void timer_vid_set_isr_timer1a_ctc (void (*callback_function) (void))
{
	timer1a_ctc_isr=callback_function;
}
void timer_vid_set_isr_timer1b_ctc (void (*callback_function) (void))
{
	timer1b_ctc_isr=callback_function;
}
void timer_vid_set_isr_timer2_ctc (void (*callback_function) (void))
{
	timer2_ctc_isr=callback_function;
}


void __vector_10 (void) __attribute__ ((signal,__INTR_ATTRS)) ;
void __vector_10 (void)
{
	timer0_ctc_isr();
}
void __vector_7(void) __attribute__ ((signal,__INTR_ATTRS)) ;
void __vector_7 (void)
{
	timer1a_ctc_isr();
}
void __vector_8(void) __attribute__ ((signal,__INTR_ATTRS)) ;
void __vector_8 (void)
{
	timer1b_ctc_isr();
}
void __vector_4(void) __attribute__ ((signal,__INTR_ATTRS)) ;
void __vector_4 (void)
{
	timer2_ctc_isr();
}






void timer_vid_init0_ctc (u16 prescalar, u8 top, u8 interrupt)
{
	/*CTC MODE*/
	setBit(TCCR0, WGM01);
	clrBit(TCCR0, WGM00);
	
	/*SETTING PRESCALAR*/
	switch (prescalar) {
		case 1:
		TCCR0 = TCCR0| 0b00000001;
		break;
		case 8:
		TCCR0 = TCCR0| 0b00000010;
		break;
		case 64:
		TCCR0 = TCCR0| 0b00000011;
		break;
		case 256:
		TCCR0 = TCCR0| 0b00000100;
		break;
		case 1024:
		TCCR0 = TCCR0| 0b00000101;
		break;
		default:
		break;
	}
	
	/*SETTING THE TOP VALUE*/
	OCR0 = top;
	
	/*ENABLE INTERRUPT*/
	if (interrupt) {
		/*ENABLE GLOBAL INTERRUPT*/
		setBit(SREG, 7);
		/*ENABLE TIMER0 INTERRUPT*/
		setBit(TIMSK, OCIE0);
	}
	else {
		clrBit(TIMSK, OCIE0);
	}
}
void timer_vid_init1_ctc (u16 prescalar, u16 top, u8 interrupt, u8 channel) 
{
	/*CTC MODE*/
	clrBit(TCCR1A, WGM10);
	clrBit(TCCR1A, WGM11);
	setBit(TCCR1B, WGM12);
	clrBit(TCCR1B, WGM13);
	
	/*SETTING PRESCALAR*/
	switch (prescalar) {
		case 1:
		TCCR1B = TCCR1B| 0b00000001;
		break;
		case 8:
		TCCR1B = TCCR1B| 0b00000010;
		break;
		case 64:
		TCCR1B = TCCR1B| 0b00000011;
		break;
		case 256:
		TCCR1B = TCCR1B| 0b00000100;
		break;
		case 1024:
		TCCR1B = TCCR1B| 0b00000101;
		break;
		default:
		break;
	}
	if (prescalar == 1)
	
	/*SETTING THE TOP VALUE*/
	switch (channel) {
		case 'A':
		OCR1AL = top;
		OCR1AH = top>>8;
		break;
		case 'B':
		OCR1BL = top;
		OCR1BH = top>>8;
		break;
		default:
		break;
	}
	/*ENABLE INTERRUPT*/
	if (interrupt) {
		/*ENABLE GLOBAL INTERRUPT*/
		setBit(SREG, 7);
		/*ENABLE TIMER0 INTERRUPT*/
		switch (channel) {
			case 'A':
			setBit(TIMSK, OCIE1A);
			clrBit(TIMSK, OCIE1B);
			break;
			case 'B':
			clrBit(TIMSK, OCIE1A);
			setBit(TIMSK, OCIE1B);
			break;
			default:
			break;
		}
	}
	else {
		clrBit(TIMSK, OCIE1A);
		clrBit(TIMSK, OCIE1B);
	}
}

void timer_vid_init2_ctc (u16 prescalar, u8 top, u8 interrupt) 
{
	/*CTC MODE*/
	setBit(TCCR2, WGM21);
	clrBit(TCCR2, WGM20);
	
	/*SETTING PRESCALAR*/
	switch (prescalar) {
		case 1:
		TCCR2 = TCCR2| 0b00000001;
		break;
		case 8:
		TCCR2 = TCCR2| 0b00000010;
		break;
		case 32:
		TCCR2 = TCCR2| 0b00000011;
		break;
		case 64:
		TCCR2 = TCCR2| 0b00000100;
		break;
		case 128:
		TCCR2 = TCCR2| 0b00000101;
		break;
		case 256:
		TCCR2 = TCCR2| 0b00000110;
		break;
		case 1024:
		TCCR2 = TCCR2| 0b00000111;
		break;
		default:
		break;
	}
	
	/*SETTING THE TOP VALUE*/
	OCR2 = top;
	
	/*ENABLE INTERRUPT*/
	if (interrupt) {
		/*ENABLE GLOBAL INTERRUPT*/
		setBit(SREG, 7);
		/*ENABLE TIMER0 INTERRUPT*/
		setBit(TIMSK, OCIE2);
	}
	else {
		clrBit(TIMSK, OCIE2);
	}
}