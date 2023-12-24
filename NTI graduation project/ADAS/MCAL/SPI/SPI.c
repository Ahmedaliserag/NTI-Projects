/*
 * SPI.c
 *
 * Created: 10/30/2023 10:01:08 AM
 *  Author: elzoz
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "SPI_Cfg.h"
#include "SPI_Reg.h"
#include "SPI.h"

static void (*Global_Ptf)(void)=NULLPTR;
static u8 *SPI_GlOBAL_DATA=NULLPTR;
void SPI_MasterCan_Init (void)
{
	/*ENABLE SPI */
	SPI_REGS->SPCR.BIT.SPE=HIGH;
	/*CHOICE MSB FIRST */
	SPI_REGS->SPCR.BIT.DORD=LOW;
	Dio_WriteChannel(PINB0,HIGH);
	/*MASTER MODE*/
	SPI_REGS->SPCR.BIT.MSTR=HIGH;
	/* CHOICE CLOCK POLARITY AND CLOCK PHASE*/
	SPI_REGS->SPCR.BIT.CPOL=LOW;  //leading rising
	SPI_REGS->SPCR.BIT.CPHA=LOW; //sampling rising
	/*CHCOICE CLOCK PRESCALLER FCPU/16 */
	SPI_REGS->SPCR.BIT.SPR0=HIGH;
	SPI_REGS->SPCR.BIT.SPR1=LOW;
	SPI_REGS->SPSR.BIT.SPI2X=LOW;
	
	//select pin ss ->>>high
}
void SPI_SlaveCan_Init (void)
{
	/*ENABLE SPI */
	SPI_REGS->SPCR.BIT.SPE=HIGH;
	/*CHOICE MSB FIRST */
	SPI_REGS->SPCR.BIT.DORD=LOW;
	/*MASTER MODE*/
	SPI_REGS->SPCR.BIT.MSTR=HIGH;
	/* CHOICE CLOCK POLARITY AND CLOCK PHASE*/
	SPI_REGS->SPCR.BIT.CPOL=LOW;  //leading rising
	SPI_REGS->SPCR.BIT.CPHA=LOW; //sampling rising
	/*CHCOICE CLOCK PRESCALLER FCPU/16 */
	SPI_REGS->SPCR.BIT.SPR0=HIGH;
	SPI_REGS->SPCR.BIT.SPR1=LOW;
	SPI_REGS->SPSR.BIT.SPI2X=LOW;
}
u8 SPI_MasterTransmit (u8 data)
{
	u8 dataRead=0;
	SPI_REGS->SPDR.R=data;
	
	while(SPI_REGS->SPSR.BIT.SPIF==LOW);
	
	dataRead=SPI_REGS->SPDR.R;
	return dataRead;
}
/*spi */
void SPI_Init(void)
{
	#if SPI_MODE == SPI_MASTER
	/*MASTER MODE*/
	SPI_REGS->SPCR.BIT.MSTR=HIGH;
	/*CHCOICE CLOCK PRESCALLER FCPU/16 */
	SPI_REGS->SPCR.BIT.SPR0=HIGH;
	SPI_REGS->SPCR.BIT.SPR1=LOW;
	SPI_REGS->SPSR.BIT.SPI2X=LOW;
	#elif SPI_MODE == SPI_SLAVE
	/*SALVE MODE*/
	SPI_REGS->SPCR.BIT.MSTR=LOW;
	#endif
	/* CHOICE CLOCK POLARITY AND CLOCK PHASE*/
	SPI_REGS->SPCR.BIT.CPOL=HIGH;
	SPI_REGS->SPCR.BIT.CPHA=HIGH;
	/*CHOICE LSB FIRST */
	SPI_REGS->SPCR.BIT.DORD=HIGH;
	/*ENABLE SPI */
	SPI_REGS->SPCR.BIT.SPE=HIGH;
}

void SPI_voidTransmateASYNC(void (*SPI_Ptf)(void),u8 data,u8 *rx_data)
{
	SPI_REGS->SPCR.BIT.SPIE=HIGH;
	/*CHEIK NULL*/
	Global_Ptf=SPI_Ptf;
	SPI_GlOBAL_DATA=rx_data;
	SPI_REGS->SPDR.R=data;
}

u8 SPI_Transieve(u8 Copy_u8_dat)
{
	Dio_WriteChannel(PINB4,LOW);
	while(SPI_REGS->SPSR.BIT.WCOL==HIGH);
	SPI_REGS->SPDR.R=Copy_u8_dat;
	while(SPI_REGS->SPSR.BIT.SPIF==LOW);
	Dio_WriteChannel(PINB4,HIGH);
	return SPI_REGS->SPDR.R;
	
}
void __vector_17(void)    __attribute__((signal));
void __vector_17(void)
{
	Global_Ptf();
	*SPI_GlOBAL_DATA=SPI_REGS->SPDR.R;
}
