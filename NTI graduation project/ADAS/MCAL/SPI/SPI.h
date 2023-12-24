/*
 * SPI.h
 *
 * Created: 10/30/2023 10:00:57 AM
 *  Author: elzoz
 */ 


#ifndef SPI_H_
#define SPI_H_


#define HIGH 1
#define LOW 0

#define SPI_MASTER 1
#define SPI_SLAVE 2

void SPI_Init(void);
u8 SPI_Transieve(u8 Copy_u8_dat);
void SPI_MasterCan_Init (void);
u8 SPI_MasterTransmit (u8 data);
void SPI_voidTransmateASYNC(void (*SPI_Ptf)(void),u8 data,u8 *rx_data);

#endif /* SPI_H_ */