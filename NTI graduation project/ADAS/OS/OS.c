#include "OS.h"

static OS_struct taskArray [MAX_NUM_OF_TASKS];
static u8 taskCounter = 0;

OS_feedback OS_TaskCreate(fncPtr local_function, u16 periodicity, OS_state default_state,u8 local_delay)
{
	OS_feedback status=OK_VALID;
   if (local_function==NULLPTR)
   {
	   status=NOK_NULL_PTR;
   }
   else if (periodicity>HYPER_PERIOD)
   {
	  status=NOK_HYPER_PERIOD_VIOLATION;
   }
   else if (taskCounter>=MAX_NUM_OF_TASKS)
   {
	   status=NOK_TASK_COUNT_VIOLATION;
   }
   else
   {
	   	taskArray[taskCounter].function=local_function;
	   	taskArray[taskCounter].task_Periodicity=periodicity;
	   	taskArray[taskCounter].task_state=default_state;
		taskArray[taskCounter].Task_tick_counter=TICK_TIME;
		taskArray[taskCounter].delay=local_delay;
	   	taskCounter++;
   }
	return status;
}

/* LInked to ISR --- Time --- Task Ststes by ms*/
void OS_Task_Handler(void)
{
  u8 Task_id;
  for (Task_id=0;Task_id<taskCounter;Task_id++)
  {
	    if (taskArray[Task_id].task_state!=SUSPENDED)
	    {
			//using in first system first delay only
		    if (taskArray[Task_id].Task_tick_counter>=taskArray[Task_id].task_Periodicity)
		    {
			    taskArray[Task_id].task_state=READY;
			    taskArray[Task_id].Task_tick_counter=TICK_TIME+taskArray[Task_id].delay; //to setup time user need after first periodicity
		    }
		    else
		    {
			    taskArray[Task_id].Task_tick_counter+=TICK_TIME;
		    }
	    }  
  }
}


void OS_TaskExecution(void)
{
	u8 Task_id;
	for(Task_id = 0; Task_id<taskCounter; Task_id++)
	{

		if(taskArray[Task_id].task_state == READY)
		{
			
			taskArray[Task_id].function();
			taskArray[Task_id].task_state = BLOCKED;
		}
	}

}
