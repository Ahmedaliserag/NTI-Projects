/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TMR1_interface.h"


void SRVM_voidOn(u8 Copy_u8Angle)
{
	/* TMR1 init at pwm mode 14 */
    TMR1_Init();
	/* Set pwm fre. = 50 */
    SetFreq_Mode_14(50);
	/* Set pwm duty cycle between 5 : 10
	 depend on desired angle[0 : 180] */
    f32 duty_cycle =  ( 5 + ((f32)Copy_u8Angle *(5/ 180.0)));
    SetDuty_Mode_14(duty_cycle);
	/* TMR1 start */
	TMR1_Start();
}


void SRVM_voidOff(void)
{
	/* TMR1 stop */
	TMR1_Stop();
}