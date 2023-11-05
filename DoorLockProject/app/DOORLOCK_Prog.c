/*services */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 16000000
#include <util/delay.h>
/*MCAL */
#include "DIO.h"
#include "Port.h"
/*HAL */
#include "EPPROM_Interface.h"
#include "LCD_Int.h"
#include "KEYPAD_Interface.h"
#include "SRVM_interface.h"
#include "DOORLOCK_Cfg.h"
#include "DOORLOCK_Interface.h"
#include "TMR1_interface.h"
/* Array password*/
u8 passwordArray[5]={0,0,0,0,0}; // default pass for first intialization on epprom
	
	u8 passwordTesting[5]={0};
	u8 checkChangeflag=0;// to check if user pressed change pass
	u8 passwordTestingFlag=0;//to check if compare pass is wrong-> 1 or right-> 0
	u8 Attempts=3;
	
	void DOORLOCK_Init (void)
	{
		Port_Init();
		LCD_Init();
		EEPROM_Init();
		KEYPAD_Init();
		SRVM_voidOn(0);
		//SetDuty_Mode_14(100);
		/* intialization epprom with default pass 12345 for first burn only */
		//EPPROM_WritePage(0x50,passwordArray,sizePass);
		
		/* reading password from epprom and set it on global varr*/
		EPPROM_SequentialRead(0x50,passwordArray,sizePass);
		LCD_SendXY(2,5);
		LCD_SendString("Welcome :)");
		_delay_ms(1000);
			
	}
	void DOORLOCK_Runnable (void)
	{
		u8 i=0;
		/* enter pass or change pass */
		LCD_Clear();
		LCD_SendXY(1,3);
		LCD_SendString("Enter Your Pass");
		LCD_SendXY(4,0);
		LCD_SendString("changePass Press(=)");
		checkChangeflag=DOORLOCKER_SetPass (passwordTesting);
		/* check  change pass request */
		if (checkChangeflag==1)
		{
			DOORLOCKER_ChangePass();		
		}
		else
		{
			/* check entered pass with real pass  wrong-> 1 or right-> 0 */
			passwordTestingFlag=DOORLOCKER_ComparePassword(passwordTesting);
			/* pass true open door  */
			if (passwordTestingFlag==0)
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
			}
			/* pass false give him some Attempts   */
			else
			{
				Attempts--;
				LCD_Clear();
				LCD_SendXY(2,5);
				LCD_SendString("Wrong Pass!");
				LCD_SendXY(3,6);
				LCD_SendNumber(Attempts);
				LCD_SendString("Attempts");
				_delay_ms(500);
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
			DOORLOCKER_SetPass(passwordArray);
			LCD_Clear();
			LCD_SendXY(2,3);
			LCD_SendString("Pass Changed");
			_delay_ms(500);
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
		u8 j=0;
		LCD_SendXY(3,7);
		while (j<sizePass)
		{
			key=KEYPAD_GetKey();
			if (key=='=') // to change pass
			{
				return 1;
			}
			if ((key>='0')&&(key<='9'))
			{
				passArr[j]=key-'0';
				LCD_SendNumber(passArr[j]);
				_delay_ms(250);
				LCD_SendXY(3,7+j);
				LCD_WriteChar('*');
				j++;
			}
		}

		while (KEYPAD_GetKey()!='C');//busy wait to enter
		return 0;
	}
	u8 DOORLOCKER_ComparePassword (u8*passTest)
	{
		u8 flag=0;
		for (u8 j=0;j<sizePass;j++)
		{
			if(passwordArray[j]!=passTest[j])
			{
				flag=1;
				return flag;
			}
		}
		return flag;
	}