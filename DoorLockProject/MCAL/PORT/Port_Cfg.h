

#ifndef PORT_CFG_H_
#define PORT_CFG_H_
#include "Port.h"

 typedef struct {
	 Dio_PortType Port;
	 Dio_PinType Pin;
	 Dio_DirectionType Dir;
	 
 }Pin_CfgType;

#endif /* PORT_CFG_H_ */