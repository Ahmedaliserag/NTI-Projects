/*services */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap.h"
#define F_CPU 16000000
#include <util/delay.h>
/*MCAL */
#include "Port.h"
#include "TMR1_interface.h"
/*HAL */
#include "EPPROM_Interface.h"
#include "LCD_Int.h"
#include "KEYPAD_Interface.h"
#include "SRVM_interface.h"
/*APP*/
#include "DOORLOCK_Cfg.h"
#include "DOORLOCK_Interface.h"


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
// 		EPPROM_WritePage(PASS_ADDRESS,passwordArray,sizePass);
// 		EPPROM_WritePage(DEFAULT_PASS_ADDRESS,passwordArray,sizePass);
		
		/* reading password from epprom and set it on global varr*/
		EPPROM_SequentialRead(PASS_ADDRESS,passwordArray,sizePass);
		LCD_SendXY(2,5);
		LCD_SendString("Welcome :)");
		_delay_ms(1000);
			
	}
	void DOORLOCK_Runnable (void)
	{
		u8 i=0;
		/* enter pass or change pass */
		LCD_Clear();
		LCD_SendXY(1,0);
		LCD_SendString("reset pass press (-)");
		LCD_SendXY(2,0);
		LCD_SendString("changePass Press(+)");
		LCD_SendXY(3,3);
		LCD_SendString("Enter Your Pass");

		checkChangeflag=DOORLOCKER_SetPass (passwordTesting);
		/* check  change pass request */
		if (checkChangeflag==1)
		{
			DOORLOCKER_ChangePass();		
		}
		else if (checkChangeflag==2)
		{
			DOORLOCKER_ResetPass();
			LCD_Clear();
			LCD_SendXY(2,0);
			LCD_SendString("pass has been reset");
			LCD_SendXY(3,3);
			LCD_SendString("set default pass");
			LCD_SendXY(4,5);
			LCD_SendString("after 1 sec");
			_delay_ms(1500);
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
				LCD_SendXY(2,4);
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
				if (Attempts==0) 
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
		u8 checkFlag=0;
		LCD_Clear();
		LCD_SendXY(1,0);
		LCD_SendString("Enter Your OldPass");
		/*take old pass from user */
		checkFlag=DOORLOCKER_SetPass(passTest); // check if user pressed numbers
		/*compare old pass with pass */
		flag=DOORLOCKER_ComparePassword (passTest);
		if (checkFlag==0)
		{
			if (flag==1)//when old pass is wrong
			{
				/* tell him wrong pass and reset system and go to enter pass screen again */
				LCD_Clear();
				LCD_SendXY(2,3);
				LCD_SendString("Wrong oldPass!");
				_delay_ms(500);
			}
			else if (flag==0)//when old pass is right
			{
				LCD_Clear();
				LCD_SendXY(1,0);
				LCD_SendString("Enter Your NewPass");
				/*take new pass*/
				DOORLOCKER_SetPass(passwordArray);
				LCD_Clear();
				LCD_SendXY(2,3);
				LCD_SendString("Pass Changed");
				_delay_ms(500);
				/* set new pass on epprom*/
				EPPROM_WritePage(PASS_ADDRESS,passwordArray,sizePass);
			}
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
		LCD_SendXY(4,7);
		while (j<sizePass)
		{
			key=KEYPAD_GetKey();
			if (key=='+') // to change pass
			{
				return 1;
			}
			else if (key=='-') // to reset pass
			{
				return 2;
			}
			if ((key>='0')&&(key<='9'))
			{
				passArr[j]=key-'0';
				LCD_SendNumber(passArr[j]);
				_delay_ms(250);
				LCD_SendXY(4,7+j);
				LCD_WriteChar('*');
				j++;
			}
		}

		while (KEYPAD_GetKey()!='C');//busy wait to enter C 
		return 0;
	}
	u8 DOORLOCKER_ComparePassword (u8*passTest)
	{
		u8 flag=0;
		for (u8 j=0;j<sizePass;j++)
		{
			if(passwordArray[j]!=passTest[j])
			{
				flag=1; //when pass is not matched 
				return flag;
			}
		}
		return flag; //pass is matched
	}
void DOORLOCKER_ResetPass (void)
{
	    EPPROM_SequentialRead(DEFAULT_PASS_ADDRESS,passwordArray,sizePass);
  		EPPROM_WritePage(PASS_ADDRESS,passwordArray,sizePass);
  		
}



