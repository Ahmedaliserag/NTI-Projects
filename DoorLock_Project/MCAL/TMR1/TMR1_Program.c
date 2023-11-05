/* UTILES_LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*MCAL*/
#include "TMR1_interface.h"
#include "TMR1_config.h"
#include "TMR1_Private.h"
#include "TMR1_register.h"
void TMR1_Init (void)
{
	/*select FAST PWM MODE */
	#if TMR1_MODE == TMR1_FAST_PWM_MODE_14
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#if TMR1_PWM_MOD == TMR1_PWM_NONINVERTING
	
	CLR_BIT(TCCR1A,COM1A0);//clr comp
	SET_BIT(TCCR1A,COM1A1);//set top
	#elif TMR1_PWM_MOD == TMR1_PWM_INVERTING
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	#endif
	#endif
	/* 	Select Mode TMR0_FAST_PWM_MODE_14   */
}
void TMR1_Start (void)
{
	#if TMR1_PRESCALER == TMR1_PRESCALER_1
	/*	SelectPreScaller=1 */
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	#elif TMR1_PRESCALER == TMR1_PRESCALER_8
	/*	SelectPreScaller=8 */
	CLR_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	#elif TMR1_PRESCALER == TMR1_PRESCALER_64
	/*	SelectPreScaller=64 */
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	#elif TMR1_PRESCALER == TMR1_PRESCALER_256
	/*	SelectPreScaller=256 */
	CLR_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	SET_BIT(TCCR1B,CS12);
	#elif TMR1_PRESCALER == TMR1_PRESCALER_1024
	/*	SelectPreScaller=1024 */
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	SET_BIT(TCCR1B,CS12);
	#endif
}
void TMR1_Stop (void)
{
	/*	stop timer */
	CLR_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
}
void TMR1_SetCompareMatchValueA (u16 copy_u16CompareValue)
{
	OCR1A=copy_u16CompareValue;
}
void SetFreq_Mode_14 (u16 freq)
{
	// under condition tick thime 4 MS
	 ICR1 =(((u32)1000000/freq)/4)-1;

	
}
void SetDuty_Mode_14 (f32 duty)
{
	#if TMR1_PWM_MOD == TMR1_PWM_NONINVERTING
	
	OCR1A=((duty*(ICR1+1))/100)-1;
	#elif TMR1_PWM_MOD == TMR1_PWM_INVERTING
	duty=100-duty;
	OCR1A=((duty*(ICR1+1))/100)-1;
	#endif
	
	
	
}