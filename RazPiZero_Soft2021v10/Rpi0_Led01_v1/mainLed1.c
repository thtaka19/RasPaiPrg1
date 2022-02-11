/**********************************************/
/* mainLed1.c :  LED controll  Main only      */
/**********************************************/

#include "gpio_LedAddress.h"
/***  gpio_LedAddress.h  Define Led addre for Pi0 , or Pi1 ***
#define GPFSEL0		0x20200000
#define GPFSEL1		0x20200004
#define GPFSEL2		0x20200008
#define GPFSEL4 	0x20200010

#define GPSET0	 	0x2020001C
#define GPSET1  	0x20200020

#define GPCLR0	 	0x20200028
#define GPCLR1  	0x2020002C

#define GPLEV0		0x20200034  // Input 
#define GPLEV1		0x20200038  // Input 
  
***/

// Number of decrement-and-test cycles. 
#define LED_GREEN16_DIR   	(0x01 << (3*6)) // Port16(=10+6)
#define LED_GREEN20_DIR     (0x01 << (3*0)) // Port20(=20+0)
#define LED_ACT_DIR      	(0x01 << (3*7)) // Port47(=40+7)

#define LED_GREEN16   		(0x01 << 16) // Port16(10+6)
#define LED_GREEN20     	(0x01 << 20) // Port20
#define LED_ACT      		(0x01 << 15) // Port47 = 32+15

#define CYCLES_PER_MS               (5000) // 2017 05
unsigned int gpfSel ;
int stateLED = 0;// counter
void ledToggle(void)
{
stateLED++;
if(stateLED%2 == 0) {
// GPIO20,GPIO16,GPIO47: Set High
		*(volatile unsigned int *)GPCLR0 = LED_GREEN20;  //0x01 << 20
		*(volatile unsigned int *)GPCLR1 = LED_ACT; // Port47= 32+15 (0x01 << 15)
	}
 else {
// GPIO20,GPIO16,GPIO47
		*(volatile unsigned int *)GPSET0 = LED_GREEN20;  //0x01 << 20
		*(volatile unsigned int *)GPSET1 = LED_ACT; // Port47
	}
}

void delay_ms(int milliseconds)
{
    long volatile cycles = milliseconds;
	int volatile  cycle0 = CYCLES_PER_MS;
     
    while (cycles != 0)
	{
        cycles--;
		cycle0 = CYCLES_PER_MS;
	  while(cycle0 != 0)
		  cycle0--;
	}
}

int main(void){
	// LED port Initial set ; GPIO20,GPIO47: Set Output mode GPIO20:
	// GPIO20:GPFSEL2 0,1,2bits=001;GPIO47:GPFSEL4 21,22,23bits=001
// 0Clean GPFSEL2 0,1,2bits=000;
gpfSel = *(volatile unsigned int *)GPFSEL2 & (unsigned int)~(0x07 << (3*(20-20))) ;
// GPIO20:GPFSEL2 0,1,2bits=001;
*(volatile unsigned int *)GPFSEL2 = gpfSel | LED_GREEN20_DIR;//0x01 << (3*0);
  
// 0Clean GPFSEL2 0,1,2bits=000; and GPIO47:GPFSEL4 21,22,23bits=001
gpfSel = *(volatile unsigned int *)GPFSEL4 & (unsigned int)~(0x07 << (3*(47-40))) ;
*(volatile unsigned int *)GPFSEL4 = gpfSel | LED_ACT_DIR;	

	while(1){
 	// Change the state of the LED. 
          ledToggle( );
    // Pause for 300 milliseconds. 
          delay_ms(300);		
	}
	return 0;
}

//***********************************************************************/
//*	GNU Linker .text/.bss Initialize routine before main function.	*/
//***********************************************************************/

extern char etext[], sdata[], edata[], sbss[] , ebss[];
void initializeMemory()   // Memory clear called from starup10.s
{
	char *src, *dst;	
	for( src = etext, dst = sdata ; dst< edata ; )  // Initial data copy
		*dst++ = *src++;		
	for( dst=sbss                 ; dst< ebss  ; )   // Bss 0 clead
		*dst++ =0;
}
void interruptServiceRoutine(void) { ///// Dummy for Interrupt called from startup10.s
}


