/*
 * MCP2515_prog.c
 *
 * Created: 12/6/2023 12:49:51 PM
 *  Author: Ahmed Serag
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/SPI/SPI_interface.h"
#include "../../HAL/CANMCB/MCP2515_inth.h"
#include "../../HAL/CANMCB/MCP2515_registers.h"
#include "../../HAL/CANMCB/MCP2515_private.h"
#include "../../HAL/CANMCB/MCP2515_cfg.h"

volatile u8 buffer[14];
u8 MCP2515_ReadRegister (u8 address)
{
	u8 readValue=0;

	//catch bus
	SPI_ChipSelect(1);
	
	// read instrunction to can read register MCP
	SPI_MasterTransmit(READ_INSTRUCTION); 
	//sending address register of mcp
	SPI_MasterTransmit(address); 
	//dont care sending data but we recieve data out
	readValue=SPI_MasterTransmit(0);
	
	//leave bus
	SPI_ChipSelect(0);
	return readValue;
}
void MCP2515_bufferGet (u8*buff)
{
	for (u8 i=0;i<14;i++)
	{
		buff[i]=buffer[i];
	}
}
void MCP2515_WriteRegister (u8 address,u8 data )
{
	//catch bus
	SPI_ChipSelect(1);
	// Write instrunction to can write on register MCP
	SPI_MasterTransmit(WRITE_INSTRUCTION);
	//sending address register of mcp
	SPI_MasterTransmit(address);
	//send data to register 
	SPI_MasterTransmit(data);
	//leave bus
	SPI_ChipSelect(0);
}
void MCP2515_Reset (void)
{
	//catch bus
	SPI_ChipSelect(1);
	
	// instrunction reset
	SPI_MasterTransmit(RESET_INSTRUCTION);
	
	//leave bus
	SPI_ChipSelect(0);

}
void MCP2515_Modify (u8 address,u8 mask,u8 data )
{
	//catch bus
	SPI_ChipSelect(1);
	
	// instrunction MODIFY
	SPI_MasterTransmit(MODIFY_INSTRUCTION);
	//sending address register of mcp
	SPI_MasterTransmit(address);
	// send maskable byte
	SPI_MasterTransmit(mask);
	// send data will be maksed
	SPI_MasterTransmit(data);
	
	//leave bus
	SPI_ChipSelect(0);
}
void MCP2515_SetBitTiming (u8 CNF1Value,u8 CNF2Value,u8 CNF3Value)
{
	MCP2515_WriteRegister(CNF1,CNF1Value);
	MCP2515_WriteRegister(CNF2,CNF2Value);
	MCP2515_WriteRegister(CNF3,CNF3Value);
}
void MCP2515_SetMode (u8 mode)
{
	MCP2515_Modify(CANCTRL,0xE0,mode<<5);//E for change last 3 bits only and shift 5 to get last 5 bits 
	
	while ((MCP2515_ReadRegister(CANSTAT)>>5)!=mode);  // to check if we selected right mode its additional 
	
}
void MCP2515_TransmiterInit(void)
{
	//spi master init
	SPI_ChipSelect(0);
	SPI_MasterCan_Init();
    
	//reset  mcp
	MCP2515_Reset();
	
	//to select config mode and enable clock 
    MCP2515_WriteRegister(CANCTRL,0x84);
	while ((MCP2515_ReadRegister(CANSTAT)>>5)!=CFG_MODE);  // to check if we selected right mode its additional
	
	//select bit timing
	MCP2515_SetBitTiming((2<<6),(1<<7)|(6<<3)|(1),(5));   //cnf1-> 0b1000000   01 for 3 TQ,cnf2 
	MCP2515_SetMode(NORMAL_MODE);
	//MCP2515_SetMode(LOOP_BACK_MODE); //loop back testing
}
void MCP2515_SendMessage(u8 bufId,u32 msgId,u8 dcl,u8*data)
{
	//catch bus
	SPI_ChipSelect(1);
	//write register
	SPI_MasterTransmit(WRITE_INSTRUCTION);
	//Send address first address on buffer
		SPI_MasterTransmit(TXB0CTRL);

	//setup priority  "mandatory"
	SPI_MasterTransmit(dcl>>6); 
	//send msgid
	SPI_MasterTransmit((u8)(msgId>>3)); //last 8 bits
	SPI_MasterTransmit((u8)(msgId<<5)); //first 3 bits
	//no there externalID
	SPI_MasterTransmit(0);
	SPI_MasterTransmit(0);
    //send dcl
	SPI_MasterTransmit(dcl&0x0f);
	//send data
	for (u8 i=0;i<(dcl&0x0f);i++)
	{
		SPI_MasterTransmit(data[i]);
	}
	//leave bus
	SPI_ChipSelect(0);
	//here you can send anothers buffers.....
	
	SPI_ChipSelect(1);
	//send request to send for buffer 0
	SPI_MasterTransmit(REQUEST_TO_SEND_B0);
	SPI_ChipSelect(0);
	
	
}


void SPI_ChipSelect (u8 state)
{
	if (state==1)
	{
		Dio_WriteChannel(SPI_SS_PIN,LOW);
	}
	else
	{
		Dio_WriteChannel(SPI_SS_PIN,HIGH);
	}
}

/*receiver */
void MCP2515_SetMask (u8 address,u32 value,u8 extendedFlag)
{
	//catch bus
	SPI_ChipSelect(1);
	SPI_MasterTransmit(WRITE_INSTRUCTION);
	SPI_MasterTransmit(address);
	
	if (extendedFlag)
	{
		SPI_MasterTransmit((u8)(value>>3)); 
		SPI_MasterTransmit((u8)(value<<5)|(1<<3)|(u8)(value>>27)); //first 3 bits and get last 3 bits  and enable extended
		SPI_MasterTransmit((u8)(value>>19)); 
		SPI_MasterTransmit((u8)(value<<11)); 	
	}
	else
	{
		SPI_MasterTransmit((u8)(value>>3)); //last 8 bits
		SPI_MasterTransmit((u8)(value<<5)); //first 3 bits
	}
	SPI_ChipSelect(0);	
}

void MCP2515_receiverInit(void)
{
	//spi master init
	SPI_ChipSelect(0);
	SPI_MasterCan_Init();
	//reset  mcp
	MCP2515_Reset();
	//to select config mode and enable clock
	MCP2515_WriteRegister(CANCTRL,0x84);
	while ((MCP2515_ReadRegister(CANSTAT)>>5)!=CFG_MODE);  // to check if we selected right mode its additional
	//select bit timing
	MCP2515_SetBitTiming(0x80,0xb1,0x5);   //cnf1-> 0b1000000   01 for 3 TQ,cnf2
	// set mask all msgs accepted
	MCP2515_SetMask(RXM0SIDH,MASK_RXB0,1);
	MCP2515_SetMask(RXM1SIDH,MASK_RXB1,1);
	//enable interrupt rx
	MCP2515_WriteRegister(CANINTE,1<<0);
	
	MCP2515_SetMode(NORMAL_MODE);
	//MCP2515_SetMode(LOOP_BACK_MODE); //loop back testing
	
}

void MCP2515_receiverB0 (void)
{
	//catch bus
	SPI_ChipSelect(1);
	SPI_MasterTransmit(READ_INSTRUCTION);
	SPI_MasterTransmit(RXB0CTRL);
	for (u8 i=0 ;i<14;i++)
	{
		buffer[i]=SPI_MasterTransmit(0);
	}
	SPI_ChipSelect(0);
	//clear interrupt rx
	MCP2515_WriteRegister(CANINTF,0);
}
