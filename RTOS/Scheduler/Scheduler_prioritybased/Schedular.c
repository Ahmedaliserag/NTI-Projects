#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GI_Interface.h"
#include "TMR0_interface.h"
#include "Schdular_int.h"
typedef struct {
	u16 periodicity;
	void (*ptf)(void);
}SCHEDULER_TYPE;

	SCHEDULER_TYPE Tasks[NO_OF_TASKS];
void Create_task (u8 priority ,u16 locad_periodicity ,void(*pf)(void))
{
	Tasks[priority].periodicity=locad_periodicity;
	Tasks[priority].ptf=pf;
}
void Scheduler (void)
{
	static u16 local_counter=1;
	u8 i=0;

	for (i=0;i<NO_OF_TASKS;i++)
	{
	if ((local_counter%Tasks[i].periodicity==0))
	{
		Tasks[i].ptf();
	}
	}
	local_counter++;
}

