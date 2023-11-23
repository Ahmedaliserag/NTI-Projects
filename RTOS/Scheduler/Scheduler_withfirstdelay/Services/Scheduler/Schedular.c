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

	SCHEDULER_TYPE Tasks[NO_OF_TASKS];
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
	Tasks[priority].periodicity=local_periodicity;
	Tasks[priority].firstdelay=local_delay;
	Tasks[priority].ptf=pf;
}
void Scheduler (void)
{
	static u16 local_counter=1;
	static u8 flag=0;
	u8 i=0;


	for (i=0;i<NO_OF_TASKS;i++)
	{
		if (local_counter<=NO_OF_TASKS&&flag==0)
		{
				if ((local_counter==Tasks[i].firstdelay))
				{
					Tasks[i].ptf();
				}
			continue;
		}
		flag=1;
	if ((local_counter%Tasks[i].periodicity==0))
	{
		Tasks[i].ptf();
	}
	}
	local_counter++;
}

