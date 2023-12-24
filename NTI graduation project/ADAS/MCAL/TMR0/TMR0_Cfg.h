/*
 * TMR_Cfg.h
 *
 * Created: 10/23/2023 11:34:36 AM
 *  Author: zeyad mostafa
 */ 


#ifndef TMR0_CFG_H_
#define TMR0_CFG_H_

#define TMR0_PRELOAD_VALUE          113
#define TMR0_OVER_FLOW_COUNTER      977
#define TMR0_CTC_COUNTER            1500
#define TMR0_MODE                   TMR0_FAST_PWM_MODE   //Use (TMR0_NORMALMODE || TMR0_CTCMODE || TMR0_FAST_PWM_MODE || TMR0_PhaseCorrect_MODE)

#define TMR0_PRESCALLER    TMR0_PRESCALLER_64       /*  
                                                    Prescallar values:  
	                                                     TMR0_PRESCALLER_1         
                                                         TMR0_PRESCALLER_8    
                                                         TMR0_PRESCALLER_64    
	                                                     TMR0_PRESCALLER_256          
	                                                     TMR0_PRESCALLER_1024   
                                                    */
  
  #define PWM_MODE     TMR0_PWM_NONINVERTING    /*FAST PWM (TMR0_PWM_NONINVERTING || TMR0_PWM_INVERTING)*/



#endif /* TMR_CFG_H_ */