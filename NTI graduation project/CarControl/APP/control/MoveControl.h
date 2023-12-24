/*
 * MoveControl.h
 *
 * Created: 11/18/2023 7:26:49 PM
 *  Author: ahmed ali
 */ 


#ifndef MOVECONTROL_H_
#define MOVECONTROL_H_


void MOTOR_Init (void);
void MOTOR_Runnable (void);

void CarDirection (void);
void CarSpeed (void);

void UART_Get (void);
void COM_handle (void);
void COM_Tx (void);
void COM_Rx (void);
//cases
#define ACC_ON 1
#define ACC_OFF 0
#define LANE_ON 1
#define LANE_OFF 0

#define ENABLE 1
#define DISABLE 0
//speed cases
#define SPEED_0 0
#define SPEED_1 1
#define SPEED_2 2
#define SPEED_3 3
#define SPEED_4 4

#endif /* MOVECONTROL_H_ */