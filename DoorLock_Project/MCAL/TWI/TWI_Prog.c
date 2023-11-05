#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TWI_Register.h"
#include "TWI_Private.h"
#include "TWI_Interface.h"
#define F_CPU 16000000
#include <util/delay.h>
void TWI_InitMaster (u8 copy_u8Add)
{
	if ((copy_u8Add<128)&&(copy_u8Add>0)) //validation
	{
		TWAR=copy_u8Add<<1; // to set address master to not trigger to slave 
	}
	/* select 400k frequency*/
	TWBR=12;  //form equ
	//select prescaler 1 
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	/* enable ACK */
	SET_BIT(TWCR,TWEA);
	/* enable TWI */
	SET_BIT(TWCR,TWEN);
	
}
void TWI_SendStartCondition (void)
{
	/* Request start condition  */
	SET_BIT(TWCR,TWSTA);// it done when flag -> 0
	SET_BIT(TWCR,TWINT);//clear flag by set it any logical change to start new job
	while (0==GET_BIT(TWCR,TWINT)); // busy wait for the flag to frame done
	while (TWI_STATUS_VALUE!=TWI_START_CONDITION_ACK); // check  ACK = SC ACK  
}
void TWI_SendRepStartCondition (void)
{
	/* Request start condition  */
	SET_BIT(TWCR,TWSTA);// it done when flag -> 0
	SET_BIT(TWCR,TWINT);//clear flag by set it any logical change to start new job
	while (0==GET_BIT(TWCR,TWINT)); // busy wait for the flag to frame done
	while (TWI_STATUS_VALUE!=TWI_REP_START_CONDITION_ACK); // check  ACK = SC ACK
}
void TWI_SendStopCondition (void)
{
	/* request stop condition */
	SET_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWINT);//clear flag by set it any logical change to start new job
	/*no setting flag after stop condition so no busy wait */
	/* no check ack */
}
void TWI_SendSlaveAddWithWrite  (u8 copy_u8SlaveAdd)
{
		if (copy_u8SlaveAdd<128) //validation
		{
			TWDR=copy_u8SlaveAdd<<1; // send frame 7 bit for address of slave sending MSB
			CLR_BIT(TWDR,0); // last bit will send it 0 -> write 
			//clear start condition bit
			
			CLR_BIT(TWCR,TWSTA);
			SET_BIT(TWCR,TWINT);//clear flag 
			while (0==GET_BIT(TWCR,TWINT)); // busy wait for the flag to frame done
			while (TWI_STATUS_VALUE!=TWI_SLAVE_ADDRESS_WRITE_ACK); // check  ACK = SC ACK
		}
}
void TWI_SendSlaveAddWithRead  (u8 copy_u8SlaveAdd)
{
	if (copy_u8SlaveAdd<128) //validation
	{
		TWDR=copy_u8SlaveAdd<<1; // send frame 7 bit for address of slave sending MSB
		SET_BIT(TWDR,0); // last bit will send it 1 -> READ
		//clear start condition bit
		CLR_BIT(TWCR,TWSTA);
		
		SET_BIT(TWCR,TWINT);//clear flag
		while (0==GET_BIT(TWCR,TWINT)); // busy wait for the flag to frame done
		while (TWI_STATUS_VALUE!=TWI_SLAVE_ADDRESS_READ_ACK); // check  ACK = SC ACK
	}
}
void TWI_WriteMasterDataByte (u8 TxData)
{
	TWDR=TxData;
	SET_BIT(TWCR,TWINT);//clear flag
	while (0==GET_BIT(TWCR,TWINT)); // busy wait for the flag
	while (TWI_STATUS_VALUE!=TWI_MASTER_DATA_TRANSMIT_ACK); // check  ACK = SC ACK
}
void TWI_ReadMasterDataByte (u8* RxData,ACK_STATUS_TYPE status)
{
	if (RxData!=NULLPTR)
	{
		switch (status)
		{
			case NACK:
			/* send NACK */
			CLR_BIT(TWCR,TWEA);
			break;
			case ACK:
			/* send ACK */
			SET_BIT(TWCR,TWEA);
			break;
		}
		SET_BIT(TWCR,TWINT);//clear flag
		while (0==GET_BIT(TWCR,TWINT)); // busy wait for the flag
		switch (status)
		{
			case NACK:
			if (TWI_STATUS_VALUE==TWI_MASTER_DATA_RECIEVE_NACK) // check  ACK = SC ACK
			{
				*RxData=TWDR; // READ DATA
			}
			break;
			case ACK:
		    if (TWI_STATUS_VALUE==TWI_MASTER_DATA_RECIEVE_ACK) // check  ACK = SC ACK
		   {
			*RxData=TWDR; // READ DATA
		    }
			break;
		}
	}
}
