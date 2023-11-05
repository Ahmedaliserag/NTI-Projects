/*services */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 16000000
#include <util/delay.h>
/*MCAL */
#include "DIO.h"
#include "Port.h"
#include "TMR1_interface.h"
/*HAL */
#include "EPPROM_Interface.h"
#include "LCD_Int.h"
#include "KEYPAD_Interface.h"
#include "SRVM_interface.h"
/* delay lib */


/* Array password*/
u8 passwordArray[5];

/* config */
#define sizePass 5
#define BUZZ PINC7
#define RED_LED PINB7

/*app prototype */
u8 DOORLOCKER_SetPass (u8*passArr);
u8 DOORLOCKER_ComparePassword (u8*passTest);
void DOORLOCKER_ChangePass (void);
void Alarm_On (void);
void Alarm_Off (void);

int main(void)
{

	/*intialization*/
	u8 passwordTesting[5]={0};
	u8 checkflag=0;
	u8 testFlag=0;
	u8 Attempts=3;
	u8 i=0;
	Port_Init();
	LCD_Init();
	EEPROM_Init();
	TMR1_Init();
	TMR1_Start();
	KEYPAD_Init();
	SRVM_voidOn(0);
	EPPROM_ReadByte(0x50,&checkflag); // for check for first time running application
	if (checkflag==0xff)
	{
		LCD_SendXY(2,5);
		LCD_SendString("Welcome :)");
		_delay_ms(1250);
		LCD_SendXY(1,0);
		LCD_SendString("Set Your First Pass");
		LCD_SendXY(2,0);
		LCD_SendString("of 5 digits    ");
		/*set pass */
		DOORLOCKER_SetPass(passwordArray);
		/*enter pass on epprom  */
		EPPROM_WritePage(0x50,passwordArray,sizePass);
		_delay_ms(250);
		LCD_Clear();
		LCD_SendXY(2,3);
		LCD_SendString("pass confirmed");
		_delay_ms(1500);
		LCD_Clear();
	}
	/* reading password from epprom and set it on global varr*/
	EPPROM_SequentialRead(0x50,passwordArray,sizePass);
	while (1)
	{
		/* enter pass or change pass */
		    LCD_Clear();
			LCD_SendXY(1,3);
			LCD_SendString("Enter Your Pass");
			LCD_SendXY(4,0);
			LCD_SendString("changePass Press(=)");
			checkflag=DOORLOCKER_SetPass (passwordTesting);
			/* check  change pass request */
			if (checkflag==1)
			{
				DOORLOCKER_ChangePass();
				continue;
			}
			/* check entered pass with real pass  */
			testFlag=DOORLOCKER_ComparePassword(passwordTesting);
			/* pass true open door  */
        if (testFlag==0)
		{
			LCD_Clear();
			LCD_SendXY(2,4);
			LCD_SendString("Welcome Home");
			SRVM_voidOn(180);
			_delay_ms(5000);
			SRVM_voidOn(0); // door closed
			LCD_Clear();
			LCD_SendXY(2,3);
			LCD_SendString("Door Closed");
			_delay_ms(1500);
			LCD_Clear();
			continue;
		}
		/* pass false give him some Attempts   */
		else if (testFlag==1)
		{
			Attempts--;
			LCD_Clear();
			LCD_SendXY(2,5);
			LCD_SendString("Wrong Pass!");
			LCD_SendXY(3,6);
			LCD_SendNumber(Attempts);
			LCD_SendString("Attempts");
			_delay_ms(500);
		}
		/* alarm on after 3 wrong pass */
		if (Attempts==0) //after third wrong pass
		{
			LCD_Clear();
			/* to reset system after 5 min here is 2500 ms */
			while(i<50)
			{
				_delay_ms(50);
				Alarm_On();
				LCD_SendXY(1,5);
				LCD_SendString("Wrong Pass!");
				LCD_SendXY(2,3);
				LCD_SendString("Restarting after");
				LCD_SendXY(3,8);
				LCD_SendString("5 min");
				i++;
			}
			Alarm_Off();
			Attempts=3;
			LCD_Clear();
		}
	}
}
void DOORLOCKER_ChangePass (void)
{
	u8 passTest[5]={0};
	u8 flag=0;
	LCD_Clear();
	LCD_SendXY(1,0);
	LCD_SendString("Enter Your OldPass");
	DOORLOCKER_SetPass(passTest);
	flag=DOORLOCKER_ComparePassword (passTest);
    if (flag==1)
	{
		LCD_Clear();
		LCD_SendXY(2,3);
		LCD_SendString("Wrong oldPass!");
		_delay_ms(500);
	}
	else if (flag==0)
	{
		LCD_Clear();
		LCD_SendXY(1,0);
		LCD_SendString("Enter Your NewPass");
		DOORLOCKER_SetPass(passTest);
		LCD_Clear();
		LCD_SendXY(2,3);
		LCD_SendString("Pass Changed");
		_delay_ms(500);
		for (u8 i=0;i<sizePass;i++)
		{
			passwordArray[i]=passTest[i];
		}
		EPPROM_WritePage(0x50,passwordArray,sizePass);
	}
	
}
void Alarm_On (void)
{
	Dio_WriteChannel(BUZZ,STD_HIGH);
	Dio_FlipChannel(RED_LED);
}
void Alarm_Off (void)
{
	Dio_WriteChannel(BUZZ,STD_LOW);
	Dio_WriteChannel(RED_LED,STD_LOW);
}
u8 DOORLOCKER_SetPass (u8*passArr)
{
	u8 key=0;
	u8 i=0;
	LCD_SendXY(3,6);
	while (i<sizePass)
	{
		key=KEYPAD_GetKey();
		if (key=='=') // to change pass
		{
			return 1;
		}
		if ((key>='0')&&(key<='9'))
		{
			passArr[i]=key-'0';
			LCD_SendNumber(passArr[i]);
			_delay_ms(250);
			LCD_SendXY(3,6+i);
			LCD_WriteChar('*');
			i++;
		}
	}
	while (KEYPAD_GetKey()!='C');//busy wait to enter 
	return 0;
}
u8 DOORLOCKER_ComparePassword (u8*passTest)
{
	u8 flag=0;
	for (u8 i=0;i<sizePass;i++)
	{
		if(passwordArray[i]!=passTest[i])
		{
			flag=1;
			return flag;
		}
	}
	return flag;
}