/*
 * MemMap.h
 *
 * Created: 10/20/2023 10:07:53 AM
 *  Author: zeyad mostafa 
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_
#define PORTA (*(volatile unsigned char*)0x3B)
#define DDRA (*(volatile unsigned char*)0x3A)
#define PINA (*(volatile unsigned char*)0x39)

#define PORTB (*(volatile unsigned char*)0x38)
#define DDRB (*(volatile unsigned char*)0x37)
#define PINB (*(volatile unsigned char*)0x36)

#define PORTC (*(volatile unsigned char*)0x35)
#define DDRC (*(volatile unsigned char*)0x34)
#define PINC (*(volatile unsigned char*)0x33)

#define PORTD (*(volatile unsigned char*)0x32)
#define DDRD (*(volatile unsigned char*)0x31)
#define PIND (*(volatile unsigned char*)0x30)


#define PORTE (*(volatile unsigned char*)0x23)
#define DDRE (*(volatile unsigned char*)0x22)
#define PINE (*(volatile unsigned char*)0x21)



/************************************************************************************************/
/* Timer 0 */

#define TCNT0   (*(volatile unsigned char*)0x52)
#define TCCR0   (*(volatile unsigned char*)0x53)
/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

#define SPMCR   (*(volatile unsigned char*)0x68)
#define TIFR    (*(volatile unsigned char*)0x56)
#define TIMSK   (*(volatile unsigned char*)0x57)
/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

#define OCR0    (*(volatile unsigned char*)0x51)
/*********************************************************************************/
/* Timer 2 */

#define OCR2     (*(volatile unsigned char*)0x43)
#define TCNT2    (*(volatile unsigned char*)0x44)
#define TCCR2    (*(volatile unsigned char*)0x45)



/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0



/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define COM1C1  3
#define COM1C0  2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* WDTCR */
#define WDTCR    (*(volatile unsigned char*)0x41)
/* bits 7-5 reserved */
#define WDCE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0


/******************************************************************************/
/*TIMER 1*/


#define ICR1      (*(volatile unsigned short*)0x46)
#define ICR1L     (*(volatile unsigned char*)0x46)
#define ICR1H     (*(volatile unsigned char*)0x47)
#define OCR1B     (*(volatile unsigned short*)0x48)
#define OCR1BL    (*(volatile unsigned char*)0x48)
#define OCR1BH    (*(volatile unsigned char*)0x49)
#define OCR1A     (*(volatile unsigned short*)0x4A)
#define OCR1AL    (*(volatile unsigned char*)0x4A)
#define OCR1AH    (*(volatile unsigned char*)0x4B)
#define TCNT1     (*(volatile unsigned short*)0x4C)
#define TCNT1L    (*(volatile unsigned char*)0x4C)
#define TCNT1H    (*(volatile unsigned char*)0x4D)
#define TCCR1B    (*(volatile unsigned char*)0x4E)
#define TCCR1A    (*(volatile unsigned char*)0x4F)

#define SFIOR     (*(volatile unsigned char*)0x50)

#define OSCCAL    (*(volatile unsigned char*)0x6F)







/********************************************************************************************************/

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect		  __vector_9
/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect			  __vector_10
/* Timer/Counter1 Capture Event */
#define TIMER1_ICU_vect		      __vector_11
/* Timer/Counter1 Compare Match A */
#define TIMER1_OCA_vect           __vector_12
/* Timer/Counter1 Compare Match B */
#define TIMER1_OCB_vect		      __vector_13
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			  __vector_14
/* Timer/Counter0 Compare Match */
#define TIMER0_OC_vect	    	  __vector_15
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			  __vector_16
/* Serial Transfer Complete */


#define BAD_vect                  __vector_default// changing the default address >> default address: points to the address 0 >>resting addres

/*interrupt functions*/


# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)
# define ret()  __asm__ __volatile__ ("ret" ::)

#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))


#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)




#endif /* MEMMAP_H_ */
