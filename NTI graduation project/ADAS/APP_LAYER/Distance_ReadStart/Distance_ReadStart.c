/*
 * Distance_ReadStart.c
 *
 * Created: 12/7/2023 4:24:07 AM
 *  Author: elzoz
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../HAL/UltraSonic/UltraSonic.h"
#include "Distance_ReadStart.h"



void Distance_ReadStart (void)
{
	 UltraSonic_Read_Distance();
}
