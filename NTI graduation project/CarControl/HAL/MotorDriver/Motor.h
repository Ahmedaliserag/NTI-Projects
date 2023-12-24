/*
 * Motor.h
 *
 * Created: 11/26/2023 9:44:55 PM
 *  Author: ahmed ali
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_


void MOTOR_Forward (void); //
void MOTOR_Backward (void); //
void MOTOR_Forward_SetSpeed (u8 speed); //
void MOTOR_Stop (void); //
void MOTOR_steering_Control(u8 steeringstatus);//
void Stop_Stering_motor (void); //


#endif /* MOTOR_H_ */