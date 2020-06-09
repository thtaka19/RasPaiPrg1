#include "rpi_timer9.h"
#include "rpi_peripherals.h"
#include "led.h"
//#include "mini_serial9Pls.h"
#include "startupAss.h"

// apb_clock = 250MHz?  --- :rpi_sysconfig.h
#define APB_CLOCK	(250000000)
void LEDblinkMsg(void);
// Timer IRQ function
//void (*timerIRQ_func)(void);

//void timerInterrupt(void)
extern volatile int timer0;
void timerIRQ_func(void)
{
	ledTogglePin(20);
	ledTogglePin(21);
	timer0 ++;
	// LED Message
//	LEDblinkMsg();

}

void LEDblinkMsg(void){

	static unsigned int led = 0;

	if(led%2==0){
		printf("LED: ON %d\r\n",led);		
	}
	else{
		printf("LED: OFF\r\n");
	}
	led++ ;
}
void set_Timer_val(int milliseconds){

	// Stop Timer
	*TIMER_CONTROL &= 0xffffff00;
	
	*TIMER_LOAD   = milliseconds*1000-1;
	*TIMER_RELOAD = milliseconds*1000-1;
	// Start 
	// Timer enable, 32bit Timer
	*TIMER_CONTROL |= 0x000000A2;
}
void init_syst(void){
	*SYST_CHI = 0;
	*SYST_CLO = 0;
}

unsigned long long int get_systime(void){
	unsigned long long int t;
	unsigned int chi;
	unsigned int clo;

	// Get counter value
	chi = *SYST_CHI;
	clo = *SYST_CLO;

	// Check carry up
	if(chi !=  *SYST_CHI){
		// If carry up, get again
		chi = *SYST_CHI;
		clo = *SYST_CLO;
	}

	// make 64bits
	t = chi;
	t = t << 32;
	t += clo;

	return t;
}


void enable_timer_interrupt(){
	// 
	*INTERRUPT_ENABLE_BASIC_IRQS |= 0x01;
	*TIMER_CONTROL |= TMR_INT_EN;
}


void disable_timer_interrupt(){
	// 
	*INTERRUPT_ENABLE_BASIC_IRQS &= 0xfffffff1;
	*TIMER_CONTROL &= ~TMR_INT_EN;
}


int set_timer_clock(unsigned int clock){
	// 
	if(clock > APB_CLOCK){
		// error
		return -1;
	}

	unsigned int prediv = APB_CLOCK / clock - 1;

	// printf("prediv = %d\n",prediv);
	// delay(10000);

	// Set pre-divider
	*TIMER_PREDIVIDER = prediv;

	return 0;
}


unsigned int get_timer_rawIRQ(void){
	return *TIMER_RAWIRQ;
}

unsigned int get_timer_maskedIRQ(void){
	return *TIMER_MASKEDIRQ;
}

void clear_timer_flag(void){
	*TIMER_IRQ_CLR = 0;
}

// Arduino Style

void Timer_initialize(unsigned int period){

	// Set timer clock : 1MHz
	set_timer_clock(1000000);

	// Timer 32bit
	*TIMER_CONTROL |= 0x00000002;

	// period(us)
//	Timer_stop();
	*TIMER_CONTROL &= ~TMR_EN;

	// Timer_start(period); Timer_setPeriod(period);
	*TIMER_RELOAD = period;
	*TIMER_LOAD = period;

}
void timerInit(void) {
	Timer_initialize(4000000);
	// Timer Start
	*TIMER_CONTROL |= TMR_EN;
}
void Timer_setPeriod(unsigned int period){
	// period(us)
	*TIMER_RELOAD = period;
	*TIMER_LOAD = period;
}

void Timer_start(void){
	// Timer Start
	*TIMER_CONTROL |= TMR_EN;
}

void Timer_stop(void){
	// Timer stop
	*TIMER_CONTROL &= ~TMR_EN;
}

unsigned int Timer_read(void){
	return *TIMER_VALUE;
}

//void Timer_attachInterrupt(void (*f)(void)){
void Timer_attachInterruptXX(void){
	// Cleat flag
	*TIMER_IRQ_CLR = 0;
	// 
//	timerIRQ_func = f;
	// 
	Timer_start();
	//
	enable_timer_interrupt();
//	enable_IRQ();
}

void Timer_dettachInterrupt(void){
	// disable interrupt
	disable_timer_interrupt();
}
