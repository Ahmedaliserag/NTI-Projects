#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_Interface.h"
#include "EPPROM_Private.h"
#include "EPPROM_Interface.h"
#define F_CPU 16000000
#include <util/delay.h>
void EEPROM_Init (void)
{
	TWI_InitMaster(255);
}
void EPPROM_WriteByte (u16 add,u8 data)
{
	/* equ slave add */
	u8 local_address = (add>>8)|EPPROM_FIXED_ADD  ; // 0x50= 0b01010000
	/* send start cond */
	TWI_SendStartCondition();
	TWI_SendSlaveAddWithWrite(local_address);
	TWI_WriteMasterDataByte((u8)add); // send WORD address as data but in epprom its address
	TWI_WriteMasterDataByte(data);
	TWI_SendStopCondition ();
	/* self timed write cycle  data ->> one byte */
	_delay_ms(5);
}
void EPPROM_WritePage (u16 add,u8*arr,u8 size)
{
	/* equ slave add */
	u8 local_address = (add>>8)|EPPROM_FIXED_ADD  ; // 0x50= 0b01010000
	/* send start cond */
	TWI_SendStartCondition();
	TWI_SendSlaveAddWithWrite(local_address);
	TWI_WriteMasterDataByte((u8)add); // send WORD address as data but in epprom its address
	for (u8 i=0;i<size;i++)
	{
		TWI_WriteMasterDataByte(arr[i]);
	}
	TWI_SendStopCondition ();
	/* self timed write cycle  data ->> one byte */
	_delay_ms(5);
}
void EPPROM_ReadByte (u16 add,u8* pRxData)
{
	/* random access read */
	if (pRxData!=NULLPTR)
	{
		/* equ slave add */
		u8 local_address = (add>>8)|EPPROM_FIXED_ADD  ; // 0x50= 0b01010000
		/* send start cond */
		TWI_SendStartCondition();
		TWI_SendSlaveAddWithWrite(local_address);
		TWI_WriteMasterDataByte((u8)add); // send WORD address as data but in epprom its address
		/* start repeated condition to read from epprom */
		TWI_SendRepStartCondition();
		/* read word address  */
		TWI_SendSlaveAddWithRead(local_address);
		/* read data*/
		TWI_ReadMasterDataByte(pRxData,NACK);
		/* stop */
		TWI_SendStopCondition ();
		/* self timed write cycle  data ->> one byte */
		_delay_ms(5);
	}
	
}
void EPPROM_SequentialRead (u16 add,u8*arr,u8 size)
{
	u8 i=0;
	if (arr!=NULLPTR)
	{
		/* equ slave add */
		u8 local_address = (add>>8)|EPPROM_FIXED_ADD  ; // 0x50= 0b01010000
		/* send start cond */
		TWI_SendStartCondition();
		TWI_SendSlaveAddWithWrite(local_address);
		TWI_WriteMasterDataByte((u8)add); // send WORD address as data but in epprom its address
		/* start repeated condition to read from epprom */
		TWI_SendRepStartCondition();
		/* read word address  */
		TWI_SendSlaveAddWithRead(local_address);
		/* read data*/
		for (i=0;i<size;i++)
		{
			if (i==(size-1)) // to send NACK at last data
			{
				TWI_ReadMasterDataByte(&arr[i],NACK);
				continue;
			}
			TWI_ReadMasterDataByte(&arr[i],ACK);
		}
		
		/* stop */
		TWI_SendStopCondition ();
		/* self timed write cycle  data ->> one byte */
		_delay_ms(5);
	}
}