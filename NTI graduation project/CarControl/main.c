/*
 * CarControl.c
 *
 * Created: 11/18/2023 4:52:41 PM
 * Author : ahmed serag
 */ 


#include "MemMap128.h"
#include "STD_TYPES.h"
#include "OS/OS.h"
#include "APP/control/MoveControl.h"
#include "OS/Tasks.h"
#include "MCAL/TIMERS/TIMERS_Int.h"
#include "MCAL/DIO/DIO.h"
#include "Services/PORT/Port.h"
#define   GLOBAL_ENABLE    sei
// ISR Callback
void vMillisIncrement(void)
{
	static u16 u16_MillisCounter=0;
	u16_MillisCounter++;
	if (u16_MillisCounter>=TICK_TIME)
	{
		//blocked -> ready if its time
		OS_Task_Handler();
		//reset counterl
		u16_MillisCounter=0;
	}
}
void vInitEcu(void)
{
	
	TIMER1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_64);
	TIMER1_OC1AMode(OCRA_TOGGLE);
	GLOBAL_ENABLE();
	TIMER1_OC1A_Enable();
	TIMER1_OC1A_SetCallBack(vMillisIncrement);
	MOTOR_Init();
}
void InitScheduler(void)
{
	//func working on ms
	OS_TaskCreate(Task_UART_Get_20mS,20,BLOCKED,0);
	OS_TaskCreate(Task_MOTOR_GetDirection_40mS,40,BLOCKED,0);
	OS_TaskCreate(Task_MOTOR_GetSpeed_50mS,50,BLOCKED,10);
	OS_TaskCreate(Task_MOTOR_COM_5mS,5,BLOCKED,0);
}


int main(void)
{
	vInitEcu();
	InitScheduler();

	while(1)
	{
		
		OS_TaskExecution();
	}
}
