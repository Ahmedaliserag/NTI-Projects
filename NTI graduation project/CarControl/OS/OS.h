
#ifndef OS_H_
#define OS_H_

#include "STD_TYPES.h"

typedef void (*fncPtr)(void);           /**< Function pointer for registering tasks. */

#define MAX_NUM_OF_TASKS            4
#define HYPER_PERIOD               200
#define TICK_TIME 5

typedef enum
{
	SUSPENDED,
	BLOCKED,
	READY
} OS_state;


/*Task Control Block*/
typedef struct
{
	fncPtr      function;
	OS_state    task_state;
	u8          task_Periodicity;
	u8          Task_tick_counter;
	u8          delay;
} OS_struct;


typedef enum
{
	OK_VALID,
	NOK_HYPER_PERIOD_VIOLATION,
	NOK_TASK_COUNT_VIOLATION,
	NOK_NULL_PTR,
	NOK_INIT
} OS_feedback;


OS_feedback OS_TaskCreate(fncPtr local_function, u16 periodicity, OS_state default_state,u8 local_first_delay);

void OS_Task_Handler(void);

void OS_TaskExecution(void);


#endif /* OS_H_ */
