/*
 * PortCfg.c
 *
 * Created: 10/20/2023 3:39:43 PM
 *  Author: Softlaptop
 */ 
#include "Port_Cfg.h"

  Pin_CfgType PinCfgs[]={
	  {Dio_PORTA,Dio_PIN0,Dio_INPUT},
	  {Dio_PORTA,Dio_PIN1,Dio_OUTPUT},
	  {Dio_PORTA,Dio_PIN2,Dio_OUTPUT},
	  {Dio_PORTA,Dio_PIN3,Dio_OUTPUT},
	  {Dio_PORTA,Dio_PIN4,Dio_OUTPUT},
	  {Dio_PORTA,Dio_PIN5,Dio_OUTPUT},
	  {Dio_PORTA,Dio_PIN6,Dio_OUTPUT},
	  {Dio_PORTA,Dio_PIN7,Dio_OUTPUT},
	    {Dio_PORTB,Dio_PIN0,Dio_OUTPUT},
		{Dio_PORTB,Dio_PIN1,Dio_OUTPUT},
		{Dio_PORTB,Dio_PIN2,Dio_OUTPUT},
		{Dio_PORTB,Dio_PIN3,Dio_OUTPUT},
		{Dio_PORTB,Dio_PIN4,Dio_OUTPUT},//SS
		{Dio_PORTB,Dio_PIN5,Dio_OUTPUT},//MOSI
		{Dio_PORTB,Dio_PIN6,Dio_OUTPUT}, //MISO
		{Dio_PORTB,Dio_PIN7,Dio_OUTPUT},//SCK
			{Dio_PORTC,Dio_PIN0,Dio_OUTPUT},
			{Dio_PORTC,Dio_PIN1,Dio_OUTPUT},
			{Dio_PORTC,Dio_PIN2,Dio_OUTPUT},
			{Dio_PORTC,Dio_PIN3,Dio_OUTPUT},
			{Dio_PORTC,Dio_PIN4,Dio_OUTPUT},
			{Dio_PORTC,Dio_PIN5,Dio_OUTPUT},
			{Dio_PORTC,Dio_PIN6,Dio_OUTPUT},
			{Dio_PORTC,Dio_PIN7,Dio_OUTPUT},
				{Dio_PORTD,Dio_PIN0,Dio_INPUT},
				{Dio_PORTD,Dio_PIN1,Dio_OUTPUT},
				{Dio_PORTD,Dio_PIN2,Dio_INPUT},
				{Dio_PORTD,Dio_PIN3,Dio_INPUT},
				{Dio_PORTD,Dio_PIN4,Dio_INPUT},
				{Dio_PORTD,Dio_PIN5,Dio_OUTPUT},
				{Dio_PORTD,Dio_PIN6,Dio_INPUT},
				{Dio_PORTD,Dio_PIN7,Dio_INPUT},
  };