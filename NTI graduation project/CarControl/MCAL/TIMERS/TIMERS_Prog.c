#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"
#include "../DIO/DIO.h"
#include "../../MCAL/TIMERS/TIMERS_Int.h"
#include "../../MCAL/TIMERS/TIMERS_private.h"
#include "../../MCAL/TIMERS/TIMERS_config.h"
/******************* TIMER0 ********************/
static void (*private_pCallBackOVF)(void)=NULLPTR;
static void (*private_pCallBackCTC)(void)=NULLPTR;
volatile static u16 private_ctcCounter;

void TMR0_Init (void)
{
  /******** Normal MODE ********/
	 #if TMR0_MODE == TMR0_NORMAL_MODE
	    /*	SelectMode=NormalMode */
	CLR_BIT(TCCR0,WGM00); 
	CLR_BIT(TCCR0,WGM01);
	    /* Init Timer with pre_load value*/
	TCNT0=TMR0_PRELOAD_VALUE;
	    /* ENABLE OVF */
	SET_BIT(TIMSK,TOIE0);
	
  /******** CTC MODE ********/
     #elif TMR0_MODE == TMR0_CTC_MODE
        /*	SelectMode=CTC Mode */
    	CLR_BIT(TCCR0,WGM00);
    	SET_BIT(TCCR0,WGM01);
		/* Enable OC Interrupt*/
		SET_BIT(TIMSK,OCIE0);
		
  /******** FAST_PWM MODE ********/
		#elif TMR0_MODE == TMR0_FAST_PWM_MODE
		/*	SelectMode=TMR0_FAST_PWM_MODE */
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		
		/*	Select Mode TMR0_FAST_PWM_MODE */
	 #if TMR0_PWM_MOD == TMR0_PWM_NONINVERTING
	 CLR_BIT(TCCR0,COM00);
	 SET_BIT(TCCR0,COM01);
	 #elif TMR0_PWM_MOD == TMR0_PWM_INVERTING
	 SET_BIT(TCCR0,COM01);
	 SET_BIT(TCCR0,COM00);
	 #endif
	 /******** PHASE_CORRECT MODE ********/
	 #elif TMR0_MODE == TMR0_PHASE_CORRECT_MODE
	 /*	SelectMode=TMR0_FAST_PWM_MODE */
	 SET_BIT(TCCR0,WGM00);
	 CLR_BIT(TCCR0,WGM01);
	 
	 /*	Select Mode OF PHASE_CORRECT  */
	 #if TMR0_PWM_MOD == TMR0_PWM_NONINVERTING
	 CLR_BIT(TCCR0,COM00);
	 SET_BIT(TCCR0,COM01);
	 #elif TMR0_PWM_MOD == TMR0_PWM_INVERTING
	 SET_BIT(TCCR0,COM01);
	 SET_BIT(TCCR0,COM00);
	 #endif
		
	#endif
}
/*   Output Compare Register */
void TMR0_SetComparematchValue (u8 copy_u8compareValue) //set value to compare 
{
	OCR0=copy_u8compareValue;
}
void TMR0_setDelay_ms_usingCTC (u16 copy_u16Delay_ms)
{
	#if TMR0_PRESCALER == TMR0_PRESCALER_1
	
	#elif TMR0_PRESCALER == TMR0_PRESCALER_8
	// under condition tick time .5ms
	OCR0=249;
	private_ctcCounter= copy_u16Delay_ms*8 ; // TimeDelay configurable delay from developer  /8=1000/125
	#elif TMR0_PRESCALER == TMR0_PRESCALER_64
	// under condition tick time 4ms
	OCR0=249;
	private_ctcCounter=copy_u16Delay_ms; // TimeDelay configurable delay from developer
	#elif TMR0_PRESCALER == TMR0_PRESCALER_256
	
	#elif TMR0_PRESCALER == TMR0_PRESCALER_1024
	
	#endif
	
}
void TMR0_Start (void)
{
	#if TMR0_PRESCALER == TMR0_PRESCALER_1
	/*	SelectPreScaller=1 */
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	#elif TMR0_PRESCALER == TMR0_PRESCALER_8
	/*	SelectPreScaller=8 */
	CLR_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	#elif TMR0_PRESCALER == TMR0_PRESCALER_64
	/*	SelectPreScaller=64 */
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	#elif TMR0_PRESCALER == TMR0_PRESCALER_256
	/*	SelectPreScaller=256 */
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	#elif TMR0_PRESCALER == TMR0_PRESCALER_1024
	/*	SelectPreScaller=1024 */
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	#endif
}
void TMR0_SetDutyCycle (u8 copy_u8DutyCycle)
{
	#if TMR0_MODE == TMR0_FAST_PWM_MODE
	if(copy_u8DutyCycle<=100)
	{
		#if TMR0_PWM_MOD == TMR0_PWM_NONINVERTING
		OCR0=(((u16) copy_u8DutyCycle *256)/100)-1;
		#elif TMR0_PWM_MOD == TMR0_PWM_INVERTING
		copy_u8DutyCycle=100-copy_u8DutyCycle;
		OCR0=(((u16) copy_u8DutyCycle *256)/100)-1;
		#endif
	}
	#elif TMR0_MODE == TMR0_PHASE_CORRECT_MODE
	if(copy_u8DutyCycle<=100)
	{
		#if TMR0_PWM_MOD == TMR0_PWM_NONINVERTING
		OCR0=(((u16) copy_u8DutyCycle *255)/100);
		#elif TMR0_PWM_MOD == TMR0_PWM_INVERTING
		copy_u8DutyCycle=100-copy_u8DutyCycle;
		OCR0=(((u16) copy_u8DutyCycle *255)/100);
		#endif
	}
	#endif
}
void TMR0_Stop (void)
{
		/*	stop timer */
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
}
/* CallBack OVF */
void TMR0_SetCallBackOVF (void(*PtrToFun)(void))
{
	if (PtrToFun!=NULLPTR) //validation to check if pointer == null or not 
	{
		private_pCallBackOVF=PtrToFun;
	}

}
/* CallBack CTC */
void TMR0_SetCallBackCTC (void(*PtrToFun)(void))
{
	if (PtrToFun!=NULLPTR)
	{
			private_pCallBackCTC=PtrToFun;
	}

}
/******************* TIMER2 ********************/

void TIMER2_Init (Timer2Mode_type local_mode,Timer2Scaler_type scaler)
{
	//Select TIMER0 Mode
	switch(local_mode)
	{
		case TIMER2_NORMAL_MODE:
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		case TIMER2_PHASECORRECT_MODE:
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		case TIMER2_CTC_MODE:
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
		case TIMER2_FASTPWM_MODE:
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	}
	TCCR2&=0xF8;//0b11111000
	scaler&=0x07;//Filter
	TCCR2|=scaler;
}

void TIMER2_OC2Mode (OC2Mode_type local_mode)
{
	switch(local_mode)
	{
		case OC2_DISCONNECTED:
		CLR_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		case OC2_TOGGLE:
		SET_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		case OC2_NON_INVERTING:
		CLR_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
		case OC2_INVERTING:
		SET_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	}
}
void TMR2_SetDutyCycle (u8 copy_u8DutyCycle)
{

	if(copy_u8DutyCycle<=100)
	{
		OCR2=(((u16) copy_u8DutyCycle *255)/100);
	}
}

/******************* TIMER1 ********************/
static void (*Timer1_OVF_Fptr)(void)=NULLPTR;
static void (*Timer1_OCA_Fptr)(void)=NULLPTR;
static void (*Timer1_OCB_Fptr)(void)=NULLPTR;
static void (*Timer1_ICU_Fptr)(void)=NULLPTR;
void TIMER1_Init (Timer1Mode_type local_mode,Timer1Scaler_type scaler)
{
	//Select TIMER1 Mode
	switch(local_mode)
	{
		case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_NORMAL_8bit_MODE:
		
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
	}
	TCCR1B&=0xF8;//0b11111000
	scaler&=0x07;//Filter
	TCCR1B|=scaler;
}
void TIMER1_OC1AMode (OC1A_Mode_type local_mode)
{
	switch(local_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		OCR1A=250;
		break;
		case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
void TIMER1_OC1BMode (OC1B_Mode_type local_mode)
{
	switch(local_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
void TIMER1_ICU_Edge(ICU_Edge_type local_edge)
{
	switch(local_edge)
	{
		case RISING:
		SET_BIT	(TCCR1B,ICES1);
		break;
		case FALLING:
		CLR_BIT(TCCR1B,ICES1);
		break;
	}
}

void TIMER1_OVF_Enable (void)
{
	SET_BIT	(TIMSK,TOIE1);
}
void TIMER1_OVF_Disable (void)
{
	CLR_BIT(TIMSK,TOIE1);
}

void TIMER1_OC1A_Enable (void)
{
	SET_BIT	(TIMSK,OCIE1A);
}
void TIMER1_OC1A_Disable (void)
{
	CLR_BIT(TIMSK,OCIE1A);
}
void TIMER1_OC1B_Enable (void)
{
	SET_BIT	(TIMSK,OCIE1B);
}
void TIMER1_OC1B_Disable (void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

void TIMER1_ICU_Enable (void)
{
	SET_BIT	(TIMSK,TICIE1);
}
void TIMER1_ICU_Disable (void)
{
	CLR_BIT(TIMSK,TICIE1);
}

void TIMER1_OVF_SetCallBack (void(*local_fptr)(void))
{
	local_fptr=Timer1_OVF_Fptr;
}
void TIMER1_OC1A_SetCallBack (void(*local_fptr)(void))
{
	Timer1_OCA_Fptr=local_fptr;
}
void TIMER1_OC1B_SetCallBack (void(*local_fptr)(void))
{
	local_fptr=Timer1_OCB_Fptr;
}
void TIMER1_ICU_SetCallBack (void(*local_fptr)(void))
{
	local_fptr=Timer1_ICU_Fptr;
}
ISR(TIMER1_OVF_vect)
{
	
	if (Timer1_OVF_Fptr!=NULLPTR)
	{
		
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if (Timer1_OCB_Fptr!=NULLPTR)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if (Timer1_OCA_Fptr!=NULLPTR)
	{
		Timer1_OCA_Fptr();
	}
}

void TIMER1_SetStartTime (u8 TIME)
{
	TCNT1=TIME;
}
