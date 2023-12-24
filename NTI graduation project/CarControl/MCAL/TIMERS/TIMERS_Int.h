


#ifndef TIMERS_INT_H_
#define TIMERS_INT_H_
/******************* TIMER0 ********************/
#define PSR10 0 // Bit 0 – PSR10: Prescaler Reset Timer/Counter1 and Timer/Counter0
void TMR0_Init (void);
void TMR0_Start (void);
void TMR0_Stop (void);
void TMR0_SetCallBackOVF (void(*PtrToFun)(void)); 
void TMR0_SetComparematchValue (u8 copy_u8compareValue);
void TMR0_SetCallBackCTC (void(*PtrToFun)(void));
void TMR0_setDelay_ms_usingCTC (u16 copy_u16Delay_ms);
void TMR0_SetDutyCycle (u8 copy_u8DutyCycle);


/******************* TIMER2 ********************/
void TIMER2_SetStartTime (u8 TIME);

typedef enum {
	TIMER2_NORMAL_MODE=0,
	TIMER2_PHASECORRECT_MODE,
	TIMER2_CTC_MODE,
	TIMER2_FASTPWM_MODE
}Timer2Mode_type;
typedef enum{
	TIMER2_STOP=0,
	TIMER2_SCALER_1,
	TIMER2_SCALER_8,
	TIMER2_SCALER_64,
	TIMER2_SCALER_256,
	TIMER2_SCALER_1024,
}Timer2Scaler_type;
typedef enum
{
	OC2_DISCONNECTED=0,
	OC2_TOGGLE,
	OC2_NON_INVERTING,
	OC2_INVERTING

}OC2Mode_type;
void TMR2_SetDutyCycle (u8 copy_u8DutyCycle);

void TIMER2_Init (Timer2Mode_type local_mode,Timer2Scaler_type scaler);
void TIMER2_OC2Mode (OC2Mode_type local_mode);
void TIMER2_OVF_Enable (void);
void TIMER2_OVF_Disable (void);
void TIMER2_OC_Enable (void);
void TIMER2_OC_Disable (void);
void TIMER2_OVF_SetCallBack (void(*local_fptr)(void));
void TIMER2_OC_SetCallBack (void(*local_fptr)(void));

/******************* TIMER1 ********************/
typedef enum {
	TIMER1_NORMAL_MODE=0,
	TIMER1_NORMAL_8bit_MODE,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE
}Timer1Mode_type;
typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	TIMER1_EXTERNALl_FALLING,
	TIMER1_EXTERNAL_RISING
}Timer1Scaler_type;
typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_type;
typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_type;
typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;
void TIMER1_Init (Timer1Mode_type local_mode,Timer1Scaler_type scaler);
void TIMER1_OC1AMode (OC1A_Mode_type local_mode);
void TIMER1_OC1BMode (OC1B_Mode_type local_mode);
void TIMER1_ICU_Edge(ICU_Edge_type local_edge);

void TIMER1_OVF_Enable (void);
void TIMER1_OVF_Disable (void);

void TIMER1_OC1A_Enable (void);
void TIMER1_OC1A_Disable (void);
void TIMER1_OC1B_Enable (void);
void TIMER1_OC1B_Disable (void);

void TIMER1_ICU_Enable (void);
void TIMER1_ICU_Disable (void);

void TIMER1_OVF_SetCallBack (void(*local_fptr)(void));
void TIMER1_OC1A_SetCallBack (void(*local_fptr)(void));
void TIMER1_OC1B_SetCallBack (void(*local_fptr)(void));
void TIMER1_ICU_SetCallBack (void(*local_fptr)(void));

void TIMER1_SetStartTime (u8 TIME);




#endif /* TIMERS_INT_H_ */