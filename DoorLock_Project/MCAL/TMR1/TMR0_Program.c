#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "TMR0_private.h"
#include "TMR0_register.h"

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
/* OVF */
void __vector_11 (void) __attribute__ ((signal));
void __vector_11 (void)
{
	/* Calling Action Indirect*/
	static u16 local_u16ovfCounter=0;
	local_u16ovfCounter++;
	if (local_u16ovfCounter==TMR0_OVER_FLOW_COUNTER)
	{
		/* Init Timer with pre_load value*/
		TCNT0=TMR0_PRELOAD_VALUE;
		/*reset counter*/
		local_u16ovfCounter=0;
		/*call action fun*/
		if (private_pCallBackOVF!=NULLPTR)//validation
		{
			private_pCallBackOVF();
		}
		
	}
}
/* CTC */
void __vector_10 (void) __attribute__ ((signal));
void __vector_10 (void)
{
	/* Calling Action Indirect*/
    static u16 local_u16ctcCounter=0;
	local_u16ctcCounter++;
	if (local_u16ctcCounter==private_ctcCounter)
	{
		/*reset counter*/
	    local_u16ctcCounter=0;	
			/*call action fun*/
		if (private_pCallBackCTC!=NULLPTR) //validation
		{
			private_pCallBackCTC();
		}
	}
}