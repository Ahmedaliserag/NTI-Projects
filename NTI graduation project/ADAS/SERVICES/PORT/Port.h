/*
 * Port.h
 *
 * Created: 10/20/2023 2:32:16 PM
 *  Author: zeyad mostafa
 */ 


#ifndef PORT_H_
#define PORT_H_



typedef enum {
	Dio_PIN0,
	Dio_PIN1,
	Dio_PIN2,
	Dio_PIN3,
	Dio_PIN4,
	Dio_PIN5,
	Dio_PIN6,
	Dio_PIN7
}Dio_PinType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;

typedef enum{
	Dio_PORTA,
	Dio_PORTB,
	Dio_PORTC,
	Dio_PORTD,
	Dio_PORTE
}Dio_PortType;

typedef enum{
	Dio_OUTPUT,
	Dio_INFREE,
	Dio_INPULL
}Dio_DirectionType;

typedef enum {
	OUTPUT,
	INFREE,
	INPULL
}Dio_PinStatus;

typedef struct {
	Dio_PortType Port;
	Dio_PinType Pin;
	Dio_DirectionType Dir;
}Pin_CfgType;



void Port_Init (void);





#endif /* PORT_H_ */
