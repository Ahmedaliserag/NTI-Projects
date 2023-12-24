#include "STD_TYPES.h"
#include "MemMap128.h"
#include "BIT_MATH.h"
#include "../../MCAL/UART/UART_Register.h"
#include "../../MCAL/UART/UART_interface.h"
#include "../../MCAL/UART/UART_Cfg.h"

static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;

void UART_Init (void)
{
	
	UBRRL = (u8) 103;
	/* Configuration of UCSRnA Register  */
	UCSRnB = ( (RXEN<<4) | (TXEN<<3) | (UCSZ2<<2) );
	/* Configure UCRnC Register to make 8-bit data & 1 stop bit & no parity  Asynchronous Mode*/
	UCSRnC = ((UMSEL << 6) | (UPM1 << 5) | (UPM0 << 4)| (USBS << 3) | (UCSZ1 << 2) | (UCSZ0 << 1));
}


void UART_TransmitData (u8 UART_DataToBeSent)
{
	while(GET_BIT(UCSRnA,5)==0);
	/* So put data in the UDR Register */
	UDR=(u8)UART_DataToBeSent;
}

u8 UART_RecieveData(void)
{
	while ( ! (UCSRnA & (1<<7)) );
	return UDR;
}

void UART_Send_String(char *ptr)
{
	u8 Iteretor=0;
	while(ptr[Iteretor]!='\0')
	{
		UART_TransmitData(ptr[Iteretor]);
		Iteretor++;
	}
}


u8 UART_ReceiveNum(void)
{
	u8 NUM1;
	NUM1 = UART_ReceiveNoBlock();
	NUM1=NUM1-'0';
	return NUM1;
}
/***********************************UART INTERRUPT**********************/
void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

void UART_SendNoBlock (u8 data)
{
	UDR = data ;
}
u8 UART_ReceiveNoBlock (void)
{
	return UDR ;
}

void __vector_18 (void) __attribute__((signal));
void __vector_18 (void)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

void __vector_20 (void) __attribute__((signal));
void __vector_20 (void)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}

