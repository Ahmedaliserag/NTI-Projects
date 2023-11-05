/*
 * TMR0_interface.h
 *
 * Created: 10/23/2023 11:36:08 AM
 *  Author: Softlaptop
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

typedef enum
{
	CS00,
	CS01,
	CS02,
	WGM01,
	COM00,
	COM01,
	WGM00,
	FOC0
}TCCR0_Type;
typedef enum
{
	TOIE0,
	OCIE0
}TIMSK_Type;
typedef enum
{
	TOV0,
	OCF0
}TIFR_Type;
#define PSR10 0 // Bit 0 – PSR10: Prescaler Reset Timer/Counter1 and Timer/Counter0

void TMR0_Init (void);
void TMR0_Start (void);
void TMR0_Stop (void);
void TMR0_SetCallBackOVF (void(*PtrToFun)(void)); 
void TMR0_SetComparematchValue (u8 copy_u8compareValue);
void TMR0_SetCallBackCTC (void(*PtrToFun)(void));
void TMR0_setDelay_ms_usingCTC (u16 copy_u16Delay_ms);
void TMR0_SetDutyCycle (u8 copy_u8DutyCycle);


#endif /* TMR0_INTERFACE_H_ */