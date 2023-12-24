/*
 * SPI_interface.h
 *
 * Created: 10/30/2023 9:53:01 AM
 *  Author: ahmed serag
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


void SPI_Init(void);
u8 SPI_Transieve(u8 Copy_u8_dat);
void SPI_MasterCan_Init (void);
u8 SPI_MasterTransmit (u8 data);
void SPI_voidTransmateASYNC(void (*SPI_Ptf)(void),u8 data,u8 *rx_data);

#endif /* SPI_INTERFACE_H_ */
