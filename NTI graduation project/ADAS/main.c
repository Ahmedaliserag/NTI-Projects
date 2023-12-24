
/*
Name : Ahmed Serag
Date : 17/10/2023
version : 1.0
SWC :
*/
#include "BIT_MATH.h"
#include "MemMap128.h"
#include "STD_TYPES.h"

#include "MCAL/DIO/DIO.h"
#include "SERVICES/PORT/Port.h"
#include "OS/OS.h"
#include "MCAL/TMR0/TMR0.h"
#include "OS/Tasks.h"
#include "MCAL/TMR1/TMR1.h"
#include "SERVICES/PORT/Port.h"
#include "HAL/MCP/MCP2515_inth.h"
#include "APP_LAYER/CAN_Communication/CAN_COMM.h"
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
    TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_64);
	TIMER0_OC0Mode(OC0_DISCONNECTED);
	TIMER0_SetStartTime(6);
	GLOBAL_ENABLE();
	TIMER0_OVF_Enable();
	TIMER0_OVF_SetCallBack(vMillisIncrement);
	TMR1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_64);
	Port_Init();	
	
	MCP2515_TransmiterInit();
	
	MCP2515_receiverInit();
	
}
void InitScheduler(void)
{
	//func working on ms
	
	OS_TaskCreate(Task_DistanceReadStart_80mS,80,BLOCKED,0);
	OS_TaskCreate(Task_EmerBreak_100mS,100,BLOCKED,20);
	OS_TaskCreate(Task_LaneKeep_40mS,40,BLOCKED,0);
	OS_TaskCreate(Task_AccCtrl_120mS,120,BLOCKED,40);
	OS_TaskCreate(Task_COM_20ms,20,BLOCKED,0);
	
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









