#include "../OS/Tasks.h"
#include "../APP/control/MoveControl.h"
#include "../MCAL/UART/UART_interface.h"
void Task_UART_Get_20mS (void)
{

	UART_Get();
	
}
void Task_MOTOR_GetSpeed_50mS(void)
{

	CarSpeed();
}
void Task_MOTOR_GetDirection_40mS(void)
{

	CarDirection();
}

void Task_MOTOR_COM_5mS(void)
{

	COM_handle();
}

