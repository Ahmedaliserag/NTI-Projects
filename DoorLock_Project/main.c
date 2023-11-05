

#include "DOORLOCK_Interface.h"



int main(void)
{
	
    DOORLOCK_Init();

	while (1)
	{
		DOORLOCK_Runnable();

	}
}
