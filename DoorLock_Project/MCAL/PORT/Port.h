/*
 * Port.h
 *
 * Created: 10/20/2023 2:32:16 PM
 *  Author: Softlaptop
 */ 


#ifndef PORT_H_
#define PORT_H_
typedef enum{
	Dio_PORTA,
	Dio_PORTB,
	Dio_PORTC,
	Dio_PORTD
}Dio_PortType;
typedef enum{
	Dio_OUTPUT,
	Dio_INPUT
}Dio_DirectionType;
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
void Port_Init (void);




#endif /* PORT_H_ */