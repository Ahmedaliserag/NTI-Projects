/*
 * Schdular_int.h
 *
 * Created: 11/17/2023 1:18:11 PM
 *  Author: Softlaptop
 */ 


#ifndef SCHDULAR_INT_H_
#define SCHDULAR_INT_H_
void Create_task (u8 priority ,u16 locad_periodicity ,void(*pf)(void));
void Scheduler (void);
#define NO_OF_TASKS 3

#endif /* SCHDULAR_INT_H_ */