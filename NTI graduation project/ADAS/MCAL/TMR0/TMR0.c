/*
 * TMR0.c
 *
 * Created: 10/23/2023 11:37:05 AM
 *  Author: zeyad mostafa
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"

#include "TMR0.h"
#include "TMR0_Cfg.h"
#include "TMR0_Private.h"

/******************* TIMER0 ********************/
static void (*Timer0_OVF_Fptr)(void)=NULLPTR;
static void (*Timer0_OC_Fptr)(void)=NULLPTR;
void TIMER0_Init (Timer0Mode_type local_mode,Timer0Scaler_type scaler)
{
	//Select TIMER0 Mode
	switch(local_mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	TCCR0&=0xF8;//0b11111000
	scaler&=0x07;//Filter
	TCCR0|=scaler;
}
void TIMER0_SetStartTime (u8 TIME)
{
	TCNT0=TIME;
}
void TIMER0_OC0Mode (OC0Mode_type local_mode)
{
	switch(local_mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}
void TIMER0_OVF_Enable (void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OVF_Disable (void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_Enable (void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_Disable (void)
{
	CLR_BIT(TIMSK,OCIE0);
}
void TIMER0_OVF_SetCallBack (void(*local_fptr)(void))
{
	Timer0_OVF_Fptr=local_fptr;
}
void TIMER0_OC_SetCallBack (void(*local_fptr)(void))
{

	Timer0_OC_Fptr=local_fptr;
}

ISR (TIMER0_OVF_vect)
{
	TCNT0=6;
	if(Timer0_OVF_Fptr!=NULLPTR)
	{
		Timer0_OVF_Fptr();
	}
}
ISR (TIMER0_OC_vect)
{
	if(Timer0_OVF_Fptr!=NULLPTR)
	{
		Timer0_OVF_Fptr();
	}
}
