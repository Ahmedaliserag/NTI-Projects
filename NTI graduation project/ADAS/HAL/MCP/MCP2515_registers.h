/*
 * MCP2515_registers.h
 *
 * Created: 12/6/2023 5:19:51 PM
 *  Author: ahmed serag
 */ 


#ifndef MCP2515_REGISTERS_H_
#define MCP2515_REGISTERS_H_

#define CNF1  (0x2A)
#define CNF2  (0x29)
#define CNF3  (0x28)

#define CANCTRL (0x0F)
#define CANSTAT (0x0E)

#define TXB0CTRL (0x30)
#define TXB1CTRL (0x40)
#define TXB2CTRL (0x50)

#define RXM0SIDH  (0x20)
#define RXM1SIDH  (0x24)
#define CANINTE  (0x2B)
#define RXB0CTRL (0b01100000)
#define RXB1CTRL (0x0E)

#define CANINTF (0x2C)



#endif /* MCP2515_REGISTERS_H_ */