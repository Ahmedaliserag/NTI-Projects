/*
 * UART_Register.h
 *
 * Created: 10/28/2023 2:22:57 PM
 *  Author: Softlaptop
 */ 


#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_



/*address of UART Control and status register A*/
#define UCSRnA (*(volatile u8*)0x2B)

/*address of UART Control and status register B*/
#define UCSRnB (*(volatile u8*)0x2A)

/*address of UART Control and status register C*/
#define UCSRnC (*(volatile u8*)0x95)

/*address of USART I/O register*/
#define UDR   (*(volatile u8*)0x2C)
#define UBRRL (*(volatile u8*)0x29)
#define UBRRH (*(volatile u8*)0x40)

#define UCSRB (*(volatile u8*)0x2A)
#define    RXCIE        7
#define    TXCIE        6


/* The equation to calculate the UBBR value */
#define MyUBRR ((u32)FOCS/((u32)16*BaudRate)-1)


#endif /* UART_REGISTER_H_ */