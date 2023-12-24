/*
 * TMR1.h
 *
 * Created: 10/25/2023 8:16:00 PM
 *  Author: zeyad mostafa
 */ 


#ifndef TMR1_H_
#define TMR1_H_

typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE, // mode 14
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_type;

typedef enum
{
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_type;

typedef enum
{
	OCRB_NON_INVERTING,
	OCRB_INVERTING
}OC1B_Mode_type;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;

void TMR1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler);
void TMR1_Init1_OCRA1Mode(OC1A_Mode_type oc1a_mode);
void TMR1_OCRB1Mode(OC1B_Mode_type oc1b_mode);
void TMR1_SetCompareMatchValueA(u16 CompareVal);
void TMR1_Stop  (void);
void PWM_Freq_HZ(u16 freq);
void PWM_Duty_Inverting(f32 duty);
void PWM_Duty_NonInverting(f32 duty);
void Timer1_InputCaptureEdge(ICU_Edge_type edge);

void Timer1_ICU_InterruptEnable(void);
void Timer1_ICU_InterruptDisable(void);

void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);

void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);

void Timer1_OCB_InterruptEnable(void);
void Timer1_OCB_InterruptDisable(void);

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void));


#endif /* TMR1_H_ */