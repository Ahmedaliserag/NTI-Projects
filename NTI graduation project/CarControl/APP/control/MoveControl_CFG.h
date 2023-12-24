/*
 * MoveControl_CFG.h
 *
 * Created: 11/18/2023 9:04:30 PM
 *  Author: ahmed ali
 */ 


#ifndef MOVECONTROL_CFG_H_
#define MOVECONTROL_CFG_H_




#define MOTOR_STOP      0
#define MOTOR_FORWARED  1
#define MOTOR_BACKWARD  2
#define MOTOR_LEFT      4
#define MOTOR_RIGHT     3
#define MOTOR_STRAIGHT  9


/* CAN MSG */
#define CAN_SPEED_MSG 1
#define CAN_DIR_MSG 2
#define CAN_EMG_MSG 3
#define CAN_ACC_MSG 1
#define CAN_LANE_MSG 2
#define CAN_EMG_FLAG_ON  1
#define CAN_ACCIDENT_FLAG_ON  1

#define CAN_ACC_ON_DLC 2
#define CAN_ACC_OFF_DLC 1
#define CAN_LANE_ON_DLC 2
#define CAN_LANE_OFF_DLC 2
#define CAN_TX_BUFF_0 0
 

#define CAN_INT_PIN PINA1
/*ACCESS KEY PIN */
#define KEY_ACCESS_PIN PINC0
/*UART MSG */
#define UART_ACC_ON_MSG 5
#define UART_ACC_OFF_MSG 6
#define UART_LANE_ON_MSG 7
#define UART_LANE_OFF_MSG 8
#define UART_MAX_NUM_MANUAL_MSG 5
/*ALARM LANE KEEP*/
#define ALARM_LANE_KEEP PINA4
#define ALARM_LANE_MSG_ON 5
#define ALARM_LANE_MSG_OFF 6
/*SPEED*/
#define SET_SPEED0 30
#define SET_SPEED1 40
#define SET_SPEED2 60
#define SET_SPEED3 80
#define SET_SPEED4 90









#endif /* MOVECONTROL_CFG_H_ */
