

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
void DOORLOCKER_ResetPass (void);


#endif /* DOORLOCK_INTERFACE_H_ */