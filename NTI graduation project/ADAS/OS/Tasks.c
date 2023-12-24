 #include "Tasks.h"
#include "../APP_LAYER/ACC_Ctrl/ACC_Ctrl.h"
#include "../APP_LAYER/Distance_ReadStart/Distance_ReadStart.h"
#include "../APP_LAYER/Emer_Break/Emer_Break.h"
#include "../APP_LAYER/Lane_Keep/Lane_Keep.h"
#include "../APP_LAYER/CAN_Communication/CAN_COMM.h"
void Task_LaneKeep_40mS (void)
{
	Lane_Keep_Control();
}
void Task_DistanceReadStart_80mS(void)
{
	Distance_ReadStart();
}
void Task_EmerBreak_100mS(void)
{
	Emergency_Break();
}
void Task_AccCtrl_120mS(void)
{
	ACC_voidUpdateSpeed();
}
void Task_COM_20ms (void)
{
	COM_handle();
}
