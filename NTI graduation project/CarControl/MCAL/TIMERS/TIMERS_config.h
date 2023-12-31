

#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_

#define TMR0_PRELOAD_VALUE 113
#define TMR0_OVER_FLOW_COUNTER 977
#define TMR0_CTC_COUNTER 4000

/* PWM */
#define TMR0_PWM_MOD TMR0_PWM_NONINVERTING
/* Select Mode 
1-TMR0_NORMAL_MODE
2-TMR0_CTC_MODE
3-TMR0_FAST_PWM_MODE
4-TMR0_PHASE_CORRECT_MODE
*/
#define TMR0_MODE TMR0_PHASE_CORRECT_MODE
/*
TMR0_PRESCALER_1 
TMR0_PRESCALER_8 
TMR0_PRESCALER_64 
TMR0_PRESCALER_256 
TMR0_PRESCALER_1024 
*/
#define TMR0_PRESCALER TMR0_PRESCALER_64


#endif /* TMR0_CONFIG_H_ */