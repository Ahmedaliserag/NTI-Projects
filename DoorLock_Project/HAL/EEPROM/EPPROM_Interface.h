/*
 * EPPROM_Interface.h
 *
 * Created: 10/31/2023 2:20:35 PM
 *  Author: Softlaptop
 */ 


#ifndef EPPROM_INTERFACE_H_
#define EPPROM_INTERFACE_H_


void EPPROM_WriteByte (u16 add,u8 data);
void EEPROM_Init (void);
void EPPROM_ReadByte (u16 add,u8* pRxData);
void EPPROM_WritePage (u16 add,u8*arr,u8 size);
void EPPROM_SequentialRead (u16 add,u8*arr,u8 size);


#endif /* EPPROM_INTERFACE_H_ */