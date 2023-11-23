/*
 * Schdular.h
 *
 *  Author: Ahmed Serag
 */ 



#ifndef SCHDULAR_INT_H_
#define SCHDULAR_INT_H_
void Create_task (u8 priority ,u16 locad_periodicity ,void(*pf)(void),u8 local_delay);
void Scheduler (void);
void Scheduler_Start (void);
#define NO_OF_TASKS 3
#define NO_OF_PRIORTY 3  // you can select tasks same priorty until No of tasks

#endif /* SCHDULAR_INT_H_ */