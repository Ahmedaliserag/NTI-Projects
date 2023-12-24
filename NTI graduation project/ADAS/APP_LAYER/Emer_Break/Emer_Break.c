
/*
 * Emer_Break.c
 *
 * Created: 11/20/2023 10:20:35 PM
 *  Author: elzoz
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"

#include "../../MCAL/DIO/DIO.h"
#include "../../HAL/UltraSonic/UltraSonic.h"
#include "Emer_Break.h"
#include "Emer_Break_Cfg.h"

volatile u8 Accedent_Flag = 0 ;
volatile u8 Emergency_Flag = 0 ;
extern u8 msgReq_3 ;

void Emergency_Break (void)
{
		u16 copy_US_Reading = UltraSonic_GetReading();
		if ((copy_US_Reading>=EMER_BREAK_1)&&(copy_US_Reading<EMER_BREAK_2))
		{
			Emergency_Flag = 1 ;
			msgReq_3 = 1 ;
		}
		else if ((copy_US_Reading>=ACCIDENT_LIMIT) && (copy_US_Reading<EMER_BREAK_1))
		{
			Emergency_Flag = 1 ;
			Accedent_Flag = 1 ;
			msgReq_3 = 1 ; 
		}
}
