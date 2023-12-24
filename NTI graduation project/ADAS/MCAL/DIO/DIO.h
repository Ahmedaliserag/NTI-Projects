/*
* DIO.h
*
* Created: 10/20/2023 10:15:22 AM
*  Author: zeyad mostafa
*/ 


#ifndef DIO_H_
#define DIO_H_

#include "../../SERVICES/PORT/Port.h"

typedef enum {
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}Dio_ChannelType;


void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level);Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif /* DIO_H_ */
