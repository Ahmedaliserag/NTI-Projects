/*
 * LCD_Int.h
 *
 * Created: 10/21/2023 1:55:08 PM
 *  Author: Softlaptop
 */ 


#ifndef LCD_INT_H_
#define LCD_INT_H_
#include "STD_TYPES.h"
#include "Dio_Types.h"
#include "Port_Cfg.h"
#include "DIO.h"
#include "BIT_MATH.h"
#include "MemMap.h"


void LCD_Init(void);
void LCD_SendCmd  (u8 cmd);
void LCD_SendData (u8 data);
void LCD_SendString (c8*str); 
void LCD_SendStringXY (u8 x,u8 y,c8*str);
void LCD_SendNumber (s32 num);
void LCD_SendXY (u8 x,u8 y);
void LCD_Clear (void);
void LCD_WriteChar (u8 ch);





#endif /* LCD_INT_H_ */