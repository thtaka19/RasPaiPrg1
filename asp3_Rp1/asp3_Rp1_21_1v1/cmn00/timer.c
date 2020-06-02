//#include "rpi_timer.h"
#include "../cmn00/rpi_peripherals.h"
#include "../cmn00/rpi_type.h"

void init_syst(void){
	*SYST_CHI = 0;
	*SYST_CLO = 0;
}
unsigned long long int get_systime(void){// Microsec System timer
	unsigned long long int t;
	unsigned int chi;
	unsigned int clo;

	// Get countervalue
	chi = *SYST_CHI;
	clo = *SYST_CLO;
	// Overflow check
	if(chi !=  *SYST_CHI){
		// if Overflow,correct chi and clo
		chi = *SYST_CHI;
		clo = *SYST_CLO;
	}
	// make for 64bits
	t = chi;
	t = t << 32;
	t += clo;

	return t;
}
void delay_ms(int milliseconds)
{
	unsigned long long alermTime;
	alermTime = get_systime() + milliseconds * 1000;	
	while(get_systime() < alermTime);
	return;
}

