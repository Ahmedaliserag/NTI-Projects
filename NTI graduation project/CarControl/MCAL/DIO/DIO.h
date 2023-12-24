


#ifndef DIO_H_
#define DIO_H_
#include "../../MCAL/DIO/Dio_Types.h"

void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level);Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif /* DIO_H_ */
