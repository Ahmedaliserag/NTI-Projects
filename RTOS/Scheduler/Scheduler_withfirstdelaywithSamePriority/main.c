#include "STD_TYPES.h"
#include "Schdular_int.h"
#include "Port.h"
#include "Tasks.h"
int main(void)
{
    Port_Init();
	Create_task(0,1,task_RedLed,0);
	Create_task(1,2,task_GreenLed,0);
	Create_task(0,3,task_BlueLed,0);
    Scheduler_Start ();
	while (1)
	{
		
	}
	
}
