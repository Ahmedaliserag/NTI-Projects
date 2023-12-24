/*
 * TMR0.h
 *
 * Created: 10/23/2023 11:34:14 AM
 *  Author: zeyad mostafa
 */ 


#ifndef TMR0_H_
#define TMR0_H_

/******************* TIMER0 ********************/
typedef enum {
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
}Timer0Mode_type;
typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}Timer0Scaler_type;
typedef enum
{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING

}OC0Mode_type;
void TIMER0_Init (Timer0Mode_type local_mode,Timer0Scaler_type scaler);
void TIMER0_OC0Mode (OC0Mode_type local_mode);
void TIMER0_OVF_Enable (void);
void TIMER0_OVF_Disable (void);
void TIMER0_OC_Enable (void);
void TIMER0_OC_Disable (void);
void TIMER0_OVF_SetCallBack (void(*local_fptr)(void));
void TIMER0_OC_SetCallBack (void(*local_fptr)(void));
void TIMER0_SetStartTime (u8 TIME);



#endif /* TMR0_H_ */