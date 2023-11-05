/*
Name : ahmed serag
Date : 17/10/2023
version : 1.0
SWC : BIT_MATH
*/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg,bit) (reg=reg|(1<<bit))
#define CLR_BIT(reg,bit) (reg=reg&(~(1<<bit)))
#define TOG_BIT(reg,bit) (reg=reg^(1<<bit))
#define GET_BIT(reg,bit) (1&(reg>>bit))




#endif /* BIT_MATH_H_ */