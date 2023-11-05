
#ifndef TMR0_REGISTER_H_
#define TMR0_REGISTER_H_
/* 8-bit Timer/Counter Register Description*/
#define TCCR0 (*(volatile unsigned char*)0x53) //Timer/Counter ControlRegister
#define TCNT0 (*(volatile unsigned char*)0x52) //Timer/Counter ControlRegister
#define OCR0 (*(volatile unsigned char*)0x5c)  //Output Compare Register 
#define TIMSK (*(volatile unsigned char*)0x59) //Timer/Counter Interrupt Mask Register
#define TIFR (*(volatile unsigned char*)0x58)  //Timer/Counter Interrupt Flag Register






#endif /* TMR0_REGISTER_H_ */