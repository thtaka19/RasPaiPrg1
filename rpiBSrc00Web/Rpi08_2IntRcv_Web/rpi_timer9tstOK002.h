#ifndef RPILIB_TIMER_H
#define RPILIB_TIMER_H
 /***
// init
void init_syst(void);

// systime
unsigned long long int get_systime(void);
***/
/***
#define mills()		(get_systime()/1000)	
#define micros()	get_systime()

// Set timer musk for "or" operation
#define	TMR_DBG_STOP	(0x00000100)
#define TMR_EN			(0x00000080)
#define TMR_INT_EN		(0x00000020)
#define TMR_BIT_32		(0x00000002)
***/
/***
void timerInit(void);
void enable_timer_interrupt(void);
void disable_timer_interrupt(void);
***/
void timerIRQ_func(void);
void set_Timer_val(int milliseconds);
void init_syst(void);
void timerInit_ms(unsigned int );

int set_timer_clock(unsigned int clock);

unsigned int get_timer_rawIRQ(void);
unsigned int get_timer_maskedIRQ(void);
void clear_timer_flag(void);

unsigned long long int get_systime(void);
/***
// Arduino Style
void Timer_initialize(unsigned int period);
void Timer_setPeriod(unsigned int period);
void Timer_start(void);
void Timer_stop(void);
unsigned int Timer_read(void);
void Timer_attachInterruptXX(void);// TT for timer9.c
// Org void Timer_attachInterrupt(void (*f)(void));
void Timer_dettachInterrupt(void);
***/

#endif
