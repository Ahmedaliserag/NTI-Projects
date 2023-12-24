/*
 * MCP2515_inth.h
 *
 * Created: 12/6/2023 12:50:04 PM
 *  Author: Ahmed Serag
 */ 


#ifndef MCP2515_INTH_H_
#define MCP2515_INTH_H_

#define HIGH 1
#define LOW 0
#define MASK_RXB0 0x00000000
#define MASK_RXB1 0x00000000
void SPI_ChipSelect (u8 state);
void MCP2515_SendMessage(u8 bufId,u32 msgId,u8 dcl,u8*data);
void MCP2515_TransmiterInit(void);
void MCP2515_SetMode (u8 mode);
void MCP2515_SetBitTiming (u8 CNF1Value,u8 CNF2Value,u8 CNF3Value);
void MCP2515_Modify (u8 address,u8 mask,u8 data );
void MCP2515_Reset (void);
void MCP2515_WriteRegister (u8 address,u8 data );
u8 MCP2515_ReadRegister (u8 address);
void MCP2515_SetMask (u8 address,u32 value,u8 extendedFlag);
void MCP2515_receiverInit(void);
void MCP2515_receiverB0 (void);
void MCP2515_bufferGet (u8*buff);



#endif /* MCP2515_INTH_H_ */
