/*
 * SPI_Cfg.h
 *
 * Created: 10/30/2023 9:53:38 AM
 *  Author: ahmed serag
 */ 


#ifndef SPI_CFG_H_
#define SPI_CFG_H_
/* options 
 1-SPI_MASTER 
 2-SPI_SLAVE */

#define SPI_MODE SPI_MASTER 
/* options  SPI Synch. / Asynch.
 1-SPI_SYNCH_ACTIVE 
 2-SPI_ASYNCH_ACTIVE */
#define SPI_ASYNCH_ACTIVE 0
#define SPI_SYNCH_ACTIVE 1
#define SPI_SYNCHRONOUS_ACTIVE SPI_ASYNCH_ACTIVE



#endif /* SPI_CFG_H_ */
