/*
 * Sensor.c
 *
 * Created: 11/28/2023 11:12:27 PM
 *  Author: elzoz
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MemMap128.h"


#include "../../MCAL/DIO/DIO.h"
#include "Sensor.h"
#include "Sensor_Cfg.h"



u8 IR_Digital_Reading (Dio_ChannelType channel)
{
	u8 Reading = 0;
	Reading = Dio_ReadChannel(channel);
	return Reading ;
}
