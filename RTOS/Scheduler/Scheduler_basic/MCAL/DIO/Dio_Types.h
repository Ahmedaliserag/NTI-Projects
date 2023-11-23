/*
 * Dio_Types.h
 *
 * Created: 10/20/2023 3:16:50 PM
 *  Author: Softlaptop
 */ 


#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_
typedef enum {
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}Dio_ChannelType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;

typedef enum {
	OUTPUT,
	INFREE,
	INPULL
}Dio_PinStatus;


#endif /* DIO_TYPES_H_ */