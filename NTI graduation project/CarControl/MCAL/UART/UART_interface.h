/*
 * UART_interface.h
 *
 * Created: 10/28/2023 1:14:11 PM
 *  Author: Ahmed Serag
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
#include "STD_TYPES.h"
#define Synchronous 0
#define Asynchronous 1

u8 UART_ReceiveId();
void UART_Init (void);
void UART_TransmitData (u8 UART_DataToBeSent);
u8 UART_RecieveData(void);
void UART_Send_String(char *ptr);
void UART_ReceiveString(u8*str);
u8 UART_ReceiveNum(void);
u8 UART_ReceiveWithTimeOut(u32 time);








void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));
void UART_SendNoBlock (u8 data);
u8   UART_ReceiveNoBlock (void);



#endif /* UART_INTERFACE_H_ */
