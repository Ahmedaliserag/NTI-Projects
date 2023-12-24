/*
 * MCP2515_private.h
 *
 * Created: 12/6/2023 5:19:17 PM
 *  Author: Ahmed Serag
 */ 


#ifndef MCP2515_PRIVATE_H_
#define MCP2515_PRIVATE_H_

#define READ_INSTRUCTION   (0x03) // 0b00000011
#define WRITE_INSTRUCTION  (0x02) //0b00000010
#define RESET_INSTRUCTION  (0xc0) //0b11000000
#define MODIFY_INSTRUCTION (0x05) //0b00000101
#define REQUEST_TO_SEND_B0 (0x81) //for buffer0

#define CFG_MODE 0x4
#define NORMAL_MODE 0x0
#define LOOP_BACK_MODE 0x2




#endif /* MCP2515_PRIVATE_H_ */
