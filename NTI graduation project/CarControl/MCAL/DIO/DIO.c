/*
 * DIO.c
 *
 * Created: 10/20/2023 10:15:07 AM
 *  Author: Ahmed Serag
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../Services/PORT/Port.h"
#include "../../MCAL/DIO/Dio_Types.h"

void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level)
{
	Dio_PortType port=ChannelId/8;
	switch(port)
	{
		case Dio_PORTA:
			if (Level)
			{
				SET_BIT(PORTA,ChannelId%8);
			}
			else
			{
				CLR_BIT(PORTA,ChannelId%8);
			}
		break;
		case Dio_PORTB :
			if (Level)
			{
				SET_BIT(PORTB,ChannelId%8);
			}
			else
			{
				CLR_BIT(PORTB,ChannelId%8);
			}
		break;
		case Dio_PORTC:
			if (Level)
			{
				SET_BIT(PORTC,ChannelId%8);
			}
			else
			{
				CLR_BIT(PORTC,ChannelId%8);
			}
		break;
		case Dio_PORTD:
			if (Level)
			{
				SET_BIT(PORTD,ChannelId%8);
			}
			else
			{
				CLR_BIT(PORTD,ChannelId%8);
			}
			break;
		case Dio_PORTE:
			if (Level)
			{
				SET_BIT(PORTE,ChannelId%8);
			}
			else
			{
				CLR_BIT(PORTE,ChannelId%8);
			}
			break;
		}
	

}
void Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	Dio_PortType port=ChannelId/8;
	u8 pin=ChannelId%8;
	switch(port)
	{
		case Dio_PORTA:
		TOG_BIT(PORTA,pin);
		break;
		case Dio_PORTB :
		TOG_BIT(PORTB,pin);
		break;
		case Dio_PORTC:
		TOG_BIT(PORTC,pin);
		break;
		case Dio_PORTD:
		TOG_BIT(PORTD,pin);
		break;
		case Dio_PORTE:
		TOG_BIT(PORTE,pin);
		break;
	}
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_PortType port=ChannelId/8;
	u8 pin=ChannelId%8;
	Dio_LevelType Level=STD_LOW;
	switch(port)
	{
		case Dio_PORTA:
			Level=GET_BIT(PINA,pin);
		break;
		case Dio_PORTB :
			Level=GET_BIT(PINB,pin);
	
		break;
		case Dio_PORTC:
			Level=GET_BIT(PINC,pin);
		break;
		case Dio_PORTD:
			Level=GET_BIT(PIND,pin);
		break;
		case Dio_PORTE:
			Level=GET_BIT(PINE,pin);
		break;
	}
	return Level;
}
