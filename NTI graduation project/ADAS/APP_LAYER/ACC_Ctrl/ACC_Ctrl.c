/*
 * ACC_Ctrl.c
 *
 * Created: 12/7/2023 2:18:27 AM
 *  Author: elzoz
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"

#include "../../MCAL/DIO/DIO.h"
#include "../../HAL/UltraSonic/UltraSonic.h"
#include "ACC_Ctrl.h"
#include "ACC_Ctrl_Cfg.h"


extern u8 Acc_flag ;
extern u8 msgReq_1 ;
volatile u8  SpeedToApply = 0;
extern u8 SetSpeed ;


u16 private_ReadDistance = 0;
u16 private_u16SetDistance = DEFAULT_DISTANCE;
f32 private_f32SpeedToApply = 0;                                                                                                                  
f32 private_f32Kp = 1.75;
s16 private_s16Error = 0;




// void ACC_voidInit(u16 speed, u16 distance)
// {
// 	Dio_FlipChannel(PINA1);
// 	/*this function assigns the
// 	 * required setpoints to the private
// 	 * variables*/
// 	/*semaphore check and take*/
// 	private_u16SetSpeed=speed;
// 	private_u16SetDistance=distance;
// 	/*semaphore give*/
// 	Dio_FlipChannel(PINA1);
// }



void ACC_voidUpdateSpeed(void)
{
	/*this function reads the distance and
	 * compares it to the required distance
	 * Based on the error, the speed in incremented or decremented
	 * by a proportional error factor Kp
	 * */
	/*check availability and take semaphore
	 * private_u16ReadDistance
	 * private_u16SetDistance
	 * private_f32SpeedToApply
	 * private_f32Kp*/
		
	if (Acc_flag == 1)
	{		
	private_ReadDistance = UltraSonic_GetReading();
	private_f32SpeedToApply =  SetSpeed;
	private_s16Error =  private_ReadDistance - private_u16SetDistance;
	private_f32SpeedToApply += (private_f32Kp * private_s16Error);
	
	if(private_f32SpeedToApply > SetSpeed)
	{
		private_f32SpeedToApply = SetSpeed;
	}
	if(private_f32SpeedToApply < MINIMUN_SPEED)
	{
		private_f32SpeedToApply = MINIMUN_SPEED;
	}
	SpeedToApply = (u8)private_f32SpeedToApply;
	msgReq_1 = 1;
	}
}
