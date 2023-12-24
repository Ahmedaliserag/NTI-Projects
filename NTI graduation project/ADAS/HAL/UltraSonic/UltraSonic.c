/*
 * UltraSonic.c
 *
 * Created: 11/18/2023 9:41:16 PM
 *  Author: elzoz
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"


#include <util/delay.h>

#include "../../MCAL/TMR1/TMR1.h"
#include "../../MCAL/DIO/DIO.h"
#include "UltraSonic.h"
#include "UltraSonic_Cfg.h"

static volatile u16 flag,t1,t2;

 u16 F_Distance = 0; 

u16 UltraSonic_GetReading(void)
{
	return F_Distance ; 
}

void UltraSonic_Read_Distance(void)
{	
	if (flag==0)
	{
		TCNT1=0;
		Dio_WriteChannel(TR,STD_HIGH);
		_delay_us(10);
		Dio_WriteChannel(TR,STD_LOW);
		Timer1_ICU_InterruptEnable();
		Timer1_ICU_SetCallBack(Func_ICU2);
		Timer1_InputCaptureEdge(RISING);
	}
}
void Func_ICU2(void)
{
	u16 Time=0;
	
	if (flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if (flag==1)
	{
		t2=ICR1;
		Timer1_ICU_InterruptDisable();
		Time=t2-t1;
		F_Distance =((Time*4)+29)/58;
		flag=0;
	}
}

