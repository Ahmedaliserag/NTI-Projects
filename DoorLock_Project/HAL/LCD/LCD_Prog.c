#include "LCD_Cfg.h"
#include "LCD_Int.h"
#define F_CPU 16000000
#include <util/delay.h>

void LCD_SendCmd  (u8 cmd)
{
	Dio_WriteChannel(RS,STD_LOW);
	
	Dio_WriteChannel(D7,GET_BIT(cmd,7));
	Dio_WriteChannel(D6,GET_BIT(cmd,6));
	Dio_WriteChannel(D5,GET_BIT(cmd,5));
	Dio_WriteChannel(D4,GET_BIT(cmd,4));
	
   Dio_WriteChannel(EN,STD_HIGH);
   _delay_ms(1);
   Dio_WriteChannel(EN,STD_LOW);
   _delay_ms(1);
   Dio_WriteChannel(D7,GET_BIT(cmd,3));
   Dio_WriteChannel(D6,GET_BIT(cmd,2));
   Dio_WriteChannel(D5,GET_BIT(cmd,1));
   Dio_WriteChannel(D4,GET_BIT(cmd,0));
   Dio_WriteChannel(EN,STD_HIGH);
   _delay_ms(1);
   Dio_WriteChannel(EN,STD_LOW);
   _delay_ms(1);
   
}
void LCD_SendData (u8 data)
{
	Dio_WriteChannel(RS,STD_HIGH);
	
	Dio_WriteChannel(D7,GET_BIT(data,7));
	Dio_WriteChannel(D6,GET_BIT(data,6));
	Dio_WriteChannel(D5,GET_BIT(data,5));
	Dio_WriteChannel(D4,GET_BIT(data,4));
	Dio_WriteChannel(EN,STD_HIGH);
	_delay_ms(1);
	Dio_WriteChannel(EN,STD_LOW);
	_delay_ms(1);
	
	Dio_WriteChannel(D7,GET_BIT(data,3));
	Dio_WriteChannel(D6,GET_BIT(data,2));
	Dio_WriteChannel(D5,GET_BIT(data,1));
	Dio_WriteChannel(D4,GET_BIT(data,0));
	Dio_WriteChannel(EN,STD_HIGH);
	_delay_ms(1);
	Dio_WriteChannel(EN,STD_LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	LCD_SendCmd(0x02);
	LCD_SendCmd(0x28);
	LCD_SendCmd(0X0c);
	LCD_SendCmd(0X01);
	_delay_ms(1);
	LCD_SendCmd(0X06);
	
}

void LCD_SendString (c8*str)
{
	u8 i=0;
	for (i=0;str[i];i++)
	{
		LCD_SendData(str[i]);
	}
}
void LCD_SendStringXY (u8 x,u8 y,c8*str)
{
		if (x==1)
		{
			LCD_SendCmd(0x80+y);
		}
		else if (x==2)
		{
			LCD_SendCmd(0xc0+y);
		}
		else if (x==3)
		{
			LCD_SendCmd(0x94+y);
		}
		else if (x==4)
		{
			LCD_SendCmd(0xd4+y);
		}
		LCD_SendString(str);
		
}
void LCD_SendXY (u8 x,u8 y)
{
		if (x==1)
		{
			LCD_SendCmd(0x80+y);
		}
		else if (x==2)
		{
			LCD_SendCmd(0xc0+y);
		}
		else if (x==3)
		{
			LCD_SendCmd(0x94+y);
		}
		else if (x==4)
		{
			LCD_SendCmd(0xd4+y);
		}
}
void LCD_SendNumber (s32 num)
{
	s8 i=0;
	u8 str[20]={0};
		if (num==0)
		{
			LCD_SendData('0');
			return ;
		}
		if (num<0)
		{
			LCD_SendData('-');
			num=num*(-1);
		}
	while (num)
	{
		str[i]=(num%10)+'0';
		num=num/10;
		i++;
	}
	
	for (i=i-1;i>=0;i--)
	{
		LCD_SendData(str[i]);
	}
}
void LCD_Clear (void)
{
	LCD_SendCmd(0x01);
}
void LCD_WriteChar (u8 ch)
{
	LCD_SendData(ch);
}