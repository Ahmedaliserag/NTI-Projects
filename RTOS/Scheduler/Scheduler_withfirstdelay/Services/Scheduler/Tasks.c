/*
 * Tasks.c
 *
 *  Author: Ahmed Serag
 */ 
#include "Tasks.h"
#include "DIO.h"
void task_RedLed (void)
{
	Dio_FlipChannel(PINA0);
}
void task_GreenLed (void)
{
	Dio_FlipChannel(PINA1);
}
void task_BlueLed (void)
{
	Dio_FlipChannel(PINA2);
}