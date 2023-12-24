/*
 * Lane_Keep.c
 *
 * Created: 11/30/2023 4:02:57 PM
 *  Author: elzoz
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"


#include "../../MCAL/DIO/DIO.h"
#include "../../HAL/Sensor/Sensor.h"
#include "Lane_Keep.h"
#include "Lane_Keep_Cfg.h"

extern u8 Acc_flag ;
extern u8 Lane_Keep_flag ;
extern u8 msgReq_2 ;
volatile u8 Direction = 2 ;

/*the output of the Lane keep function is the direction variable set to 3 
different options and handled in manual MCU 
1 -> Right direction 
2 -> Straight forward  
3 -> left direction 
 there is a forth output (ALARM) set when ACC is OFF and it is used to fire
 an alarm only when leaving the lane */

void Lane_Keep_Control (void)
{
	if (Acc_flag == 1) // checking system 
	{
		if ((IR_Digital_Reading(RIGHT_IR)) == 1)      // get read from the right side IR 
		{
			Direction = LEFT ;                 // Move left
		}
		else if ((IR_Digital_Reading(LEFT_IR)) == 1)  // get read from the left side IR
		{
			Direction = RIGHT;                 // move right
		}
		else
		{
			Direction = STRAIGHT ;             // keep straight
		}
		msgReq_2 = 1 ;
	}
	else if ((Acc_flag == 0) && (Lane_Keep_flag == 1) )
	{
		if (IR_Digital_Reading(RIGHT_IR) == 1)
		{
			Direction = ALARM_ON;                 // fire alarm when leaving lane
		}
		else if (IR_Digital_Reading(LEFT_IR) == 1)
		{
			Direction = ALARM_ON;                 // fire alarm when leaving lane
		}
		else  
		{
			Direction = ALARM_OFF;
		}
		msgReq_2 = 1 ;
	}
}
