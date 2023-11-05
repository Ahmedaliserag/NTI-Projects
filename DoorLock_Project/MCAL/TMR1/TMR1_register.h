/*
 * TMR1_register.h
 *
 * Created: 10/29/2023 10:44:02 AM
 *  Author: Softlaptop
 */ 


#ifndef TMR1_REGISTER_H_
#define TMR1_REGISTER_H_

#define TCCR1A (*(volatile u8*)0x4F)
#define TCCR1B (*(volatile u8*)0x4E)

typedef enum {
	WGM10,
	WGM11,
	FOC1B,
	FOC1A,
	COM1B0,
	COM1B1,
	COM1A0,
	COM1A1
}Control_RegisterA_Type;
#define TCNT1 (*(volatile unsigned short*)0x4C)
#define OCR1A (*(volatile unsigned short*)0x4A)
#define OCR1B (*(volatile unsigned short*)0x48)
#define ICR1 (*(volatile unsigned short*)0x46)

#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4


#endif /* TMR1_REGISTER_H_ */