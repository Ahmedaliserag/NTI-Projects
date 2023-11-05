/*
 * DOORLOCK_Interface.h
 *
 * Created: 11/5/2023 9:29:37 AM
 *  Author: Softlaptop
 */ 


#ifndef DOORLOCK_INTERFACE_H_
#define DOORLOCK_INTERFACE_H_
#include "STD_TYPES.h"

/*app prototype */
u8 DOORLOCKER_SetPass (u8*passArr);
u8 DOORLOCKER_ComparePassword (u8*passTest);
void DOORLOCKER_ChangePass (void);
void Alarm_On (void);
void Alarm_Off (void);
void DOORLOCK_Init (void);
void DOORLOCK_Runnable (void);


#endif /* DOORLOCK_INTERFACE_H_ */