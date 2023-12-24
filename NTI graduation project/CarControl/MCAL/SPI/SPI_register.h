/*
 * SPI_register.h
 *
 * Created: 10/30/2023 9:53:20 AM
 *  Author: ahmed serag
 */ 


#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_
typedef struct
{

	union
	{
		u8 R;
		struct
		{
			u8 SPR0:1;
			u8 SPR1:1;
			u8 CPHA:1;
			u8 CPOL:1;
			u8 MSTR:1;
			u8 DORD:1;
			u8 SPE :1;
			u8 SPIE:1;
		}BIT;

	}SPCR;



	union
	{
		u8 R;
		struct
		{
			u8 SPI2X:1;
			u8 UNused:5;
			u8 WCOL:1;
			u8 SPIF:1;

		}BIT;

	}SPSR;

	union
	{
		u8 R;
		struct
		{


		};

	}SPDR;

}SPI_t;



#define SPI_REGS    ((volatile SPI_t *)0x2D)



#endif /* SPI_REGISTER_H_ */
