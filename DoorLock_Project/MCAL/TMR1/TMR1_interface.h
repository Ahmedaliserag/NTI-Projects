/*
 * TMR1_interface.h
 *
 * Created: 10/29/2023 10:43:47 AM
 *  Author: Softlaptop
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_
#define TMR1_FAST_PWM_MODE_14 1

void TMR1_Init (void);
void SetFreq_Mode_14 (u16 freq);
void SetDuty_Mode_14 (f32 duty);
void TMR1_Stop (void);
void TMR1_SetCompareMatchValueA (u16 copy_u16CompareValue);
void TMR1_Start (void);


#define CS10 0
#define CS11 1
#define CS12 2


#endif /* TMR1_INTERFACE_H_ */