/*
 * Port.c
 *
 * Created: 10/20/2023 2:32:05 PM
 *  Author: Softlaptop
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap.h"
#include "Port.h"
#include "Port_Cfg.h"
extern Pin_CfgType PinCfgs[];					   
void Port_Init (void)
{
	u8 i=0;
	for (i=0;i<32;i++)
	{
		switch (PinCfgs[i].Port)
		{
			case Dio_PORTA:
			if (PinCfgs[i].Dir==Dio_OUTPUT)
			{
				SET_BIT(DDRA,PinCfgs[i].Pin);		
			}
			else
			{
				CLR_BIT(DDRA,PinCfgs[i].Pin);
			}
			break;
			case Dio_PORTB:
			if (PinCfgs[i].Dir==Dio_OUTPUT)
			{
				SET_BIT(DDRB,PinCfgs[i].Pin);
			}
			else
			{
				CLR_BIT(DDRB,PinCfgs[i].Pin);

			}
			break;
				case Dio_PORTC:
				if (PinCfgs[i].Dir==Dio_OUTPUT)
				{
					SET_BIT(DDRC,PinCfgs[i].Pin);
				}
				else
				{
					CLR_BIT(DDRC,PinCfgs[i].Pin);
	                SET_BIT(PORTD,PinCfgs[i].Pin);
				}
				break;
					case Dio_PORTD:
					if (PinCfgs[i].Dir==Dio_OUTPUT)
					{
						SET_BIT(DDRD,PinCfgs[i].Pin);
					}
					else
					{
						
						CLR_BIT(DDRD,PinCfgs[i].Pin);
						SET_BIT(PORTD,PinCfgs[i].Pin);
					}
					break;
		}
	}
}
