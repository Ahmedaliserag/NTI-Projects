/*
 * TWI_Interface.h
 *
 * Created: 10/31/2023 10:51:44 AM
 *  Author: Softlaptop
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum {
	NACK,
	ACK
	}ACK_STATUS_TYPE;

void TWI_InitMaster (u8 copy_u8Add); //(u8 copy_u8Add) in slave init
void TWI_SendStartCondition (void);
void TWI_SendRepStartCondition (void);
void TWI_SendStopCondition (void);
void TWI_SendSlaveAddWithWrite  (u8 copy_u8SlaveAdd);
void TWI_SendSlaveAddWithRead  (u8 copy_u8SlaveAdd);
void TWI_WriteMasterDataByte (u8 TxData);
void TWI_ReadMasterDataByte (u8* RxData,ACK_STATUS_TYPE status);


#endif /* TWI_INTERFACE_H_ */