/*
 * Schdular.c
 *
 *  Author: Ahmed Serag
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GI_Interface.h"
#include "TMR0_interface.h"
#include "Schdular_int.h"
typedef struct {
	u16 periodicity;
	u8 firstdelay;
	void (*ptf)(void);
	
}SCHEDULER_TYPE;

	SCHEDULER_TYPE Tasks[NO_OF_PRIORTY][NO_OF_TASKS]={0};
	static u8 tasksCounter=0;
void Scheduler_Start (void)
{
	TMR0_Init();
	GI_Enable();
	TMR0_SetCallBackCTC(Scheduler);
	TMR0_SetComparematchValue(249);
	TMR0_Start();
}
void Create_task (u8 priority ,u16 local_periodicity ,void(*pf)(void),u8 local_delay)
{
	Tasks[0][tasksCounter].periodicity=local_periodicity;
	Tasks[0][tasksCounter].firstdelay=local_delay;
	Tasks[priority][tasksCounter].ptf=pf;
	tasksCounter++;
}
void Scheduler (void)
{
	static u16 local_counter=1;
	static u8 flag=0;
	u8 i=0,j=0;
	for (j=0;j<NO_OF_PRIORTY;j++)
	{
		for (i=0;i<NO_OF_TASKS;i++)
		{
				if (local_counter<=NO_OF_TASKS&&flag==0)
				{
					if ((local_counter==Tasks[0][i].firstdelay))
					{
						if (Tasks[j][i].ptf!=0)
						{
							Tasks[j][i].ptf();
						}
					}
					continue;
				}
				flag=1;
				if ((local_counter%Tasks[0][i].periodicity==0))
				{
					if (Tasks[j][i].ptf!=0)
					{
						Tasks[j][i].ptf();
					}
				}	
		}
		local_counter++;
    }
}

