#include "STD_TYPES.h"
#include "KEYPAD_Cfg.h"
#include "KEYPAD_Interface.h"
#include "DIO.h"
#include "Dio_Types.h"
#define F_CPU 16000000
#include <util/delay.h>
extern const u8 KeysArr[ROW][COL];
void KEYPAD_Init (void)
{
	u8 i=0;
	for (i=0;i<ROW;i++)
	{
		Dio_WriteChannel(FIRST_OUTPUT-i,STD_HIGH);
	}
}
u8 KEYPAD_GetKey (void)
{
	u8 i=0,j=0;
	u8 key=NO_KEY;
	for (i=0;i<ROW;i++)
	{
		Dio_WriteChannel(FIRST_OUTPUT-i,STD_LOW);
		for (j=0;j<(COL-2);j++)
		{
			if (Dio_ReadChannel(FIRST_INPUT-j)==0)
			{
				key=KeysArr[i][j];
				_delay_ms(10);
				while (Dio_ReadChannel(FIRST_INPUT-j)==0);
			}
		}
		if (Dio_ReadChannel(PIND4)==0)
		{
			key=KeysArr[i][2];
			_delay_ms(10);
			while (Dio_ReadChannel(PIND4)==0);
		}
		if (Dio_ReadChannel(PIND3)==0)
		{
			key=KeysArr[i][3];
			_delay_ms(10);
			while (Dio_ReadChannel(PIND3)==0);
		}
		Dio_WriteChannel(FIRST_OUTPUT-i,STD_HIGH);
	}
	return key;
}