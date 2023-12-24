/*
* Move_Control.c
*
* Created: 11/18/2023 7:26:29 PM
*  Author: ahmed ali
*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"

#include "../../Services/PORT/Port.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../APP/control/MoveControl.h"
#include "../../APP/control/MoveControl_CFG.h"
#include "../../MCAL/UART/UART_interface.h"
#include "../../HAL/MotorDriver/Motor.h"
#include "../../MCAL/TIMERS/TIMERS_Int.h"
#include "../../HAL/CANMCB/MCP2515_inth.h"
volatile u8  UART_DATA ; // to save the UART_DATA received from UART in RAM
volatile u8  UART_FLAG;
volatile u8  MANIUAL_FLAG;
volatile u8  ACC_FLAG;
volatile u8  LANE_KEEP_FLAG;
static   u8 speed_UART ;
static volatile  u8 default_speed ;
/* can communications var */
static  volatile u8 speed_COM ;
static  volatile u8 dir_COM ;
volatile u8 msgReq1;
volatile u8 msgReq2;

u8 print_flag ;
u8 FristTimeOnAcc  ;
u8 motor_status ;

/*************************************************ISR FUNC******************************************/

void RX_Interrupt (void)
{
	//read UART buffer
	UART_DATA= UART_ReceiveNum(); //Read data with no block
	UART_FLAG=ENABLE;
}


/*********************************************Init & Runnble*******************************************/

void MOTOR_Init (void)
{
	Port_Init();
	while (Dio_ReadChannel(KEY_ACCESS_PIN)==DISABLE);// key access  off
	TMR0_Init();
	TMR0_Start();
	TIMER2_Init(TIMER2_PHASECORRECT_MODE,TIMER2_SCALER_64);
	TIMER2_OC2Mode(OC2_NON_INVERTING);
 	UART_Init();
    MCP2515_TransmiterInit();
	MCP2515_receiverInit();
	UART_RX_SetCallBack(RX_Interrupt);
	UART_RX_InterruptEnable();
	UART_Send_String("5/ACC ON - 6/ACC OFF - 7/lane on - 8/lane off - 9/save zone \r\n");

	
	
}

void UART_Get (void)
{
	if (UART_FLAG==ENABLE) // if UART Received any data save it in (UART_DATA) And CLR the flag
	{
		
	if(UART_DATA<UART_MAX_NUM_MANUAL_MSG) //MANUAL_mode
	{
		
		MANIUAL_FLAG = ENABLE ; 
		
	}
	if (UART_DATA==UART_ACC_ON_MSG) //ACC mode on
	{
		
		ACC_FLAG = ENABLE ; 
		LANE_KEEP_FLAG=ENABLE;
	}
	if(UART_DATA==UART_ACC_OFF_MSG) // ACC mode off
	{
		UART_Send_String("\r\n ACC IS OFF RETURN TO MANIUAL MODE \r\n");
		ACC_FLAG =DISABLE ;
		LANE_KEEP_FLAG=DISABLE;
		MANIUAL_FLAG=ENABLE;
		msgReq1=ENABLE; //send msg acc
	}
	if(UART_DATA==UART_LANE_ON_MSG) // lane keep on
	{
		UART_Send_String("\r\n lanekeep on \r\n");
		LANE_KEEP_FLAG =ENABLE ;
		MANIUAL_FLAG=DISABLE;
		msgReq2=ENABLE; //send msg lanekeep
	}
	if(UART_DATA==UART_LANE_OFF_MSG) // lane keep off
	{
		UART_Send_String("\r\n lanekeep oFF \r\n");
		LANE_KEEP_FLAG=DISABLE;
		MANIUAL_FLAG=ENABLE;
		msgReq2=ENABLE; //send msg lanekeep
	}
	UART_FLAG=DISABLE;	
}
	
}




void CarDirection (void)
{
	
	if (MANIUAL_FLAG==ENABLE && ACC_FLAG == DISABLE)//IF  ACC Off
	{
		
		motor_status = UART_DATA ;
		
		//motor_status from uart data
		switch (motor_status)
		{
			
			case MOTOR_LEFT :  MOTOR_steering_Control (MOTOR_LEFT) ;   break;
			case MOTOR_RIGHT:  MOTOR_steering_Control (MOTOR_RIGHT) ;  break;
			case MOTOR_STRAIGHT:  MOTOR_steering_Control (MOTOR_STRAIGHT) ;  break;
		}
	}
	
	if (LANE_KEEP_FLAG==ENABLE)
	{
		if(dir_COM==ALARM_LANE_MSG_ON)// if acc off but lane keep on set alarm
		{
			Dio_WriteChannel(ALARM_LANE_KEEP,STD_HIGH);
		}
		else if(dir_COM==ALARM_LANE_MSG_OFF)// if acc off but lane keep on set alarm
		{
			Dio_WriteChannel(ALARM_LANE_KEEP,STD_LOW);
		}
		else
		{
			//read spi and set on motor_status
			MOTOR_steering_Control(dir_COM); //3 RIGHt   4 LEFT    9 STRAIGHT   
		}
	}
}

void CarSpeed (void)
{
	static u8 flag=DISABLE;
	
	if (MANIUAL_FLAG==ENABLE && ACC_FLAG == DISABLE)//IF NOT ACC ON
	{
		
		motor_status = UART_DATA ;
		
		//motor_status from uart data
		switch (motor_status)
		{
			case MOTOR_STOP :      MOTOR_Stop();     break ;
			case MOTOR_FORWARED:   MOTOR_Forward();  break ;
			case MOTOR_BACKWARD:   MOTOR_Backward(); break ;
		}
		
	}
	
	
	if ( ACC_FLAG == ENABLE ) //IF ACC ON
	{
			
			flag=ENABLE;
			
			speed_UART = UART_DATA ; //save speed from uart to use it at frist time in acc mode
			if (FristTimeOnAcc==DISABLE)
			{
				switch (speed_UART)
				{
					case SPEED_0 : speed_COM = SET_SPEED0 ; default_speed = SET_SPEED0; MOTOR_Forward_SetSpeed(speed_COM); FristTimeOnAcc=ENABLE; msgReq1=ENABLE; break;
					case SPEED_1 : speed_COM = SET_SPEED1 ; default_speed = SET_SPEED1 ; MOTOR_Forward_SetSpeed(speed_COM); FristTimeOnAcc=ENABLE; msgReq1=ENABLE; break;
					case SPEED_2 : speed_COM = SET_SPEED2 ; default_speed = SET_SPEED2 ; MOTOR_Forward_SetSpeed(speed_COM); FristTimeOnAcc=ENABLE; msgReq1=ENABLE; break;
					case SPEED_3 : speed_COM = SET_SPEED3 ; default_speed = SET_SPEED3 ; MOTOR_Forward_SetSpeed(speed_COM); FristTimeOnAcc=ENABLE; msgReq1=ENABLE; break;
					case SPEED_4 : speed_COM = SET_SPEED4 ; default_speed = SET_SPEED4 ; MOTOR_Forward_SetSpeed(speed_COM); FristTimeOnAcc=ENABLE; msgReq1=ENABLE; break;
				}
			}
			
			
			if(print_flag==DISABLE) // that means we still waiting the frist speed from the user
			{
				UART_Send_String("\r\n ACC IS ON PRESS 6 TO OFF THE MODE \r\n");
				UART_Send_String("\r\n enter speed \r\n");
				print_flag=ENABLE;
			}
			
			if(FristTimeOnAcc == ENABLE )
			{
				MOTOR_Forward_SetSpeed(speed_COM);
				
			}
			
	}
		
		if(ACC_FLAG==DISABLE&&flag==ENABLE)
	 {
			/*when go out from acc mode motor will not stop and will continue with its last speed status in (acc on) 
			until read another motor status for the motor thrue uart*/
			 MOTOR_Forward_SetSpeed(default_speed); 
			 FristTimeOnAcc=DISABLE; 
			 flag=DISABLE;
	 }
}

void COM_handle (void)
{
     //transmit msg
	 COM_Tx(); 
	 // receiver  msg
	 COM_Rx ();
	
}
void COM_Tx (void)
{
	u8 accData[2]={ACC_FLAG,speed_COM};
	u8 laneFlag=LANE_KEEP_FLAG;
	/* transmit msg */
	if (msgReq1) // check if ecu want send acc msg
	{
		UART_Send_String("ACC SENT \r\n");
		switch (ACC_FLAG)
		{
			case ACC_OFF:
			//msg1 2 byte first byte acc flag on or off ,second byte speed of car
			MCP2515_SendMessage(CAN_TX_BUFF_0,CAN_ACC_MSG,CAN_ACC_OFF_DLC,&accData[0]);
			break;
			case ACC_ON:
			//msg1 2 byte first byte acc flag on or off ,second byte speed of car
			MCP2515_SendMessage(CAN_TX_BUFF_0,CAN_ACC_MSG,CAN_ACC_ON_DLC,accData);
			
			break;
		}
		msgReq1=DISABLE; // to disable req
	}
	else if (msgReq2)
	{
		switch (LANE_KEEP_FLAG)
		{
			case LANE_OFF:
			//msg2 1 byte lane flag on or off
			MCP2515_SendMessage(CAN_TX_BUFF_0,CAN_LANE_MSG,CAN_LANE_OFF_DLC,&laneFlag);
			break;
			case LANE_ON:
			//msg2 1 byte lane flag on or off
			MCP2515_SendMessage(CAN_TX_BUFF_0,CAN_LANE_MSG,CAN_LANE_ON_DLC,&laneFlag);
			break;
		}
		msgReq2=DISABLE;// to disable req
		UART_Send_String("LANE SENT \r\n");
	}
}
void COM_Rx (void)
{
	  u8 msgId=DISABLE;
	  u8 recvData[14]={0};
	  // msg1 ->> speed acc
	  // msg2 ->> dir
	  //msg3 ->> emg
	  
	if (Dio_ReadChannel(CAN_INT_PIN)==LOW)
	{
		MCP2515_bufferGet(recvData);//get frame data
		MCP2515_receiverB0();
		msgId=((recvData[2])>>5);
		if (msgId==CAN_SPEED_MSG)
		{
			speed_COM=recvData[6];
			msgId=DISABLE;	
			UART_Send_String("ACC RECV \r\n");
		}
		else if (msgId==CAN_DIR_MSG)
		{
			dir_COM=recvData[6]; 
			msgId=DISABLE;
			UART_Send_String("LANE RECV \r\n");
		}
		else if (msgId==CAN_EMG_MSG)
		{
			UART_Send_String("EMG RECV \r\n");
			if (recvData[6]==CAN_EMG_FLAG_ON)
			{
				ACC_FLAG=DISABLE;
				LANE_KEEP_FLAG=DISABLE;
				MOTOR_Stop();
				MANIUAL_FLAG=ENABLE;
				UART_DATA=DISABLE;
				if (recvData[7]==CAN_ACCIDENT_FLAG_ON)
				{
					//accident 
				}
			}
			msgId=DISABLE;
		}
	}
}
