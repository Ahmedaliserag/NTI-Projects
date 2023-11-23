#include "BIT_MATH.h"
#include "GI_Interface.h"
#include "GI_register.h"

void GI_Enable (void)
{
	SET_BIT(SREG,I);
}
void GI_Disable (void)
{
	CLR_BIT(SREG,I);
}