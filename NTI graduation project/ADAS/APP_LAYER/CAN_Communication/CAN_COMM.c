/*
 * CAN_COMM.c
 *
 * Created: 12/12/2023 8:15:08 PM
 *  Author: ahmed serag
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"
#include "../../MCAL/DIO/DIO.h"
#include "CAN_COMM.h"
#include "../../HAL/MCP/MCP2515_inth.h"



volatile u8 msgReq_1 =0;        // ACC REQ
volatile u8 msgReq_2 =0;		 // LANEKEEP REQ
volatile u8 msgReq_3 =0;		 // EMER_BREAK REQ
volatile u8 Acc_flag = 0 ;
volatile u8 Lane_Keep_flag = 0;
volatile u8 SetSpeed = 0 ;
extern u8 SpeedToApply ;
extern u8 Direction ;
extern u8 Emergency_Flag ;
extern u8 Accedent_Flag ;

/*buffer CAN */
void COM_handle (void)
{

	//transmit msg
	COM_Tx();
	// receiver  msg
	COM_Rx ();
}
void COM_Tx (void)
{
	u8 emgBreak[2]={Emergency_Flag,Accedent_Flag};
	if (msgReq_3==1)
	{
		//Dio_WriteChannel(PINA4,STD_HIGH);
		MCP2515_SendMessage(0,3,2,emgBreak);
		msgReq_3=0;
		Accedent_Flag=0;
		Emergency_Flag=0;
		Acc_flag=0;
		Lane_Keep_flag=0;
	}
	else if (msgReq_2==1)
	{
		//Dio_WriteChannel(PINA7,STD_HIGH);
		//Dio_FlipChannel(PINA5);
		MCP2515_SendMessage(0,2,1,&Direction);
		msgReq_2=0;
	}
	else if (msgReq_1==1)
	{

		MCP2515_SendMessage(0,1,1,&SpeedToApply);
		msgReq_1=0;
	}
}

void COM_Rx (void)
{
	 u8 msgId=0;
	 u8 buff[14];
	 // msg1 ->> speed acc
	 // msg2 ->> dir
	 
	 if (Dio_ReadChannel(PINA1)==0)
	 {
		 MCP2515_receiverB0();
		 MCP2515_bufferGet(buff);
		 msgId=(((buff[2])>>5));
		 if (msgId==1) // reciev data of acc msg
		 {
			
              if (buff[6]==1)
			  {
				  Acc_flag=1;
				  SetSpeed=buff[7];
			  }
			  else if (buff[6]==0)
			  {
				  Acc_flag=0;
			  }
			  
			 msgId=0;
		 }
		 else if (msgId==2) //msg lane keep 
		 {
			 
                 if (buff[6]==1)
				 {
					 Lane_Keep_flag=1;
				 }
				 else if (buff[6]==0)
				 {
					 Lane_Keep_flag=0;
				 }
			 msgId=0;
		 }
	 }
}



