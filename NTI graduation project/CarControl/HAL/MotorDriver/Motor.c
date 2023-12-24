/*
 * Motor.c
 *
 * Created: 11/26/2023 9:45:09 PM
 *  Author: ahmed ali
 */ 
#include "STD_TYPES.h"
#include "MemMap128.h"
#include "BIT_MATH.h"

#include "../../HAL/MotorDriver/Motor.h"
#include "../../HAL/MotorDriver/Motor_Cfg.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMERS/TIMERS_Int.h"






void MOTOR_Forward (void)
{
	TMR0_SetDutyCycle(MOTOR_F_DUTY); //PWM on Timer Pin
	Dio_WriteChannel(I3,STD_HIGH);
	Dio_WriteChannel(I4,STD_LOW);
}

void MOTOR_Backward (void)
{
	TMR0_SetDutyCycle(MOTOR_B_DUTY); //PWM on Timer Pin
	Dio_WriteChannel(I3,STD_LOW);
	Dio_WriteChannel(I4,STD_HIGH);
}

void MOTOR_Stop (void)
{
	TMR0_SetDutyCycle(0); //PWM on Timer Pin
	Dio_WriteChannel(I3,STD_LOW);
	Dio_WriteChannel(I4,STD_LOW);
}

void MOTOR_Forward_SetSpeed (u8 speed)
{
		TMR0_SetDutyCycle(speed);
		Dio_WriteChannel(I3,STD_HIGH);
		Dio_WriteChannel(I4,STD_LOW);
}
/*******************************steering motor******************************************************************/

void MOTOR_steering_Control(u8 steeringstatus)
{
	//1 step on
	//off motor
	
	switch (steeringstatus)
	{
		case STEERING_RIGHT  :
		Dio_WriteChannel(I1,STD_HIGH);
		Dio_WriteChannel(I2,STD_LOW);
		TMR2_SetDutyCycle(MOTOR_R_DUTY);
		break;
		case STEERING_LEFT :
		Dio_WriteChannel(I1,STD_LOW);
		Dio_WriteChannel(I2,STD_HIGH);
		TMR2_SetDutyCycle(MOTOR_L_DUTY);
		break;
		case STEERING_STRAIGHT :
		Dio_WriteChannel(I1,STD_LOW);
		Dio_WriteChannel(I2,STD_LOW);
		TMR2_SetDutyCycle(0);
		break;
	}
}
