/*
 * Schdular.h
 *
 *  Author: Ahmed Serag
 */ 



#ifndef SCHDULAR_INT_H_
#define SCHDULAR_INT_H_
void Create_task (u8 priority ,u16 local_periodicity ,void(*pf)(void),u8 local_delay);
void Scheduler_Start (void);
void Scheduler (void);
#define NO_OF_TASKS 3

#endif /* SCHDULAR_INT_H_ */