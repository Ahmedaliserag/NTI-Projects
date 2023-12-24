/*
 * PortCfg.c
 *
 * Created: 10/20/2023 3:39:43 PM
 *  Author: zeyad mostafa
 */ 
#include "Port.h"

  Pin_CfgType PinCfgs[]={
		  {Dio_PORTA,Dio_PIN0,Dio_OUTPUT},
		  {Dio_PORTA,Dio_PIN1,Dio_INFREE},
		  {Dio_PORTA,Dio_PIN2,Dio_OUTPUT},
	      {Dio_PORTA,Dio_PIN3,Dio_OUTPUT},
	 	  {Dio_PORTA,Dio_PIN4,Dio_OUTPUT},
	      {Dio_PORTA,Dio_PIN5,Dio_OUTPUT},
	      {Dio_PORTA,Dio_PIN6,Dio_OUTPUT},
	      {Dio_PORTA,Dio_PIN7,Dio_OUTPUT},
			  {Dio_PORTB,Dio_PIN0,Dio_OUTPUT}, //SS
			  {Dio_PORTB,Dio_PIN1,Dio_OUTPUT}, //CLK
			  {Dio_PORTB,Dio_PIN2,Dio_OUTPUT}, //mosi
			  {Dio_PORTB,Dio_PIN3,Dio_INFREE}, //miso
			  {Dio_PORTB,Dio_PIN4,Dio_OUTPUT},
			  {Dio_PORTB,Dio_PIN5,Dio_OUTPUT},
			  {Dio_PORTB,Dio_PIN6,Dio_OUTPUT},
			  {Dio_PORTB,Dio_PIN7,Dio_OUTPUT},
				  {Dio_PORTC,Dio_PIN0,Dio_OUTPUT},
				  {Dio_PORTC,Dio_PIN1,Dio_OUTPUT},
				  {Dio_PORTC,Dio_PIN2,Dio_OUTPUT},
				  {Dio_PORTC,Dio_PIN3,Dio_OUTPUT},
				  {Dio_PORTC,Dio_PIN4,Dio_OUTPUT},
				  {Dio_PORTC,Dio_PIN5,Dio_OUTPUT},
				  {Dio_PORTC,Dio_PIN6,Dio_INFREE},
				  {Dio_PORTC,Dio_PIN7,Dio_INFREE},
					  {Dio_PORTD,Dio_PIN0,Dio_INFREE},
					  {Dio_PORTD,Dio_PIN1,Dio_OUTPUT},
					  {Dio_PORTD,Dio_PIN2,Dio_INFREE},//can
					  {Dio_PORTD,Dio_PIN3,Dio_INPULL},
					  {Dio_PORTD,Dio_PIN4,Dio_INFREE},// echo ultrasonic
					  {Dio_PORTD,Dio_PIN5,Dio_INPULL},
					  {Dio_PORTD,Dio_PIN6,Dio_INFREE},
					  {Dio_PORTD,Dio_PIN7,Dio_OUTPUT}, // tr ultrasonic
					         {Dio_PORTE,Dio_PIN0,Dio_OUTPUT},
					  		 {Dio_PORTE,Dio_PIN1,Dio_OUTPUT},
					  		 {Dio_PORTE,Dio_PIN2,Dio_OUTPUT},
					  		 {Dio_PORTE,Dio_PIN3,Dio_OUTPUT},
					  		 {Dio_PORTE,Dio_PIN4,Dio_OUTPUT},
					  		 {Dio_PORTE,Dio_PIN5,Dio_OUTPUT},
					  		 {Dio_PORTE,Dio_PIN6,Dio_OUTPUT},
					  		 {Dio_PORTE,Dio_PIN7,Dio_OUTPUT},
  };
  
  
