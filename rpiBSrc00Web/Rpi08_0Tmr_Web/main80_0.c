//#include "rpi1.h"
// peripherals
#include "rpi_peripherals.h"
// gpio
#include "rpi_gpio.h"
#include "led.h"
#include "mini_serial.h"
#include "startupAss.h"
#include "atoix_itoa.h"
#define CYCLES_PER_MS               (10000) // 2015 05 atoix_itoa.h
#define LED_GREEN20   (0x01 << 20) // GPIO 20
#define LED_RED21     (0x01 << 21)  // GPIO 21
//#define printf m_serialPutStr  // Not yet m_serialPutStr 

//void ledOn(unsigned int mask);
//void ledOff(unsigned int mask);
void delay(int );
void set_vector_table(void){
	extern void *_initial_vector_start;
	extern void *_initial_vector_end;

	volatile unsigned int *vec = 0;
	volatile unsigned int *p;
	volatile unsigned int *s = (unsigned int *)&_initial_vector_start;
	volatile unsigned int *e = (unsigned int *)&_initial_vector_end;

	m_serialPutStr("Vector table check\r\n");
	m_serialPutStr("Addr : Hex\r\n");
	vec++;
	for (p = s+1; p < e; p++) {
		*vec = *p;
//		printf("0x%02x : 0x%08x\r\n",vec,*vec);
		vec++;
m_serialPutStr("-");
	}
}

//  When Timer interrupt comes, do (Led On/Off).
void timerIRQ_func(void){
	ledTogglePin(20);
	ledTogglePin(21);
	// LED Message
	static unsigned int led = 0;

	if(led%2==0){
		m_serialPutStr("LED: ON \r\n");
	}
	else{
		m_serialPutStr("LED: OFF\r\n");
	}

	led++ ;
}

// IRQ interrupt handler
void interruptServiceRoutine(void) { // Called from startup10.s , when any IRQ interrupte

	disable_IRQ();

	// check Basic IRQ pending
	if(*INTERRUPT_IRQ_BASIC_PENDING & 0x01 != 0){
		// timer interrupt ?
		m_serialPutStr("Timer IRQ start\r\n");
		
		timerIRQ_func();// Led on/off
		
		*TIMER_IRQ_CLR = 0;// clear flag

		m_serialPutStr("Timer IRQ end\r\n");
	}
	delay(10);

	enable_IRQ();
	return;
}

void delay(int milliseconds)
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

int main(void)
{
    char rcvChar = 0;
    char xvalC[20];
    unsigned int xval;
    /* Configure the UART for the serial driver. */
    // serialInit();

	disableInstructionCache();
	disableDataCache();
	disableMMU();
	disable_IRQ();

    	ledInit();
    	m_serialInit();// mini_Serial Init 
	// Serial Init (mini_UART) 
//	serialInit();
	// Set Vector table
	m_serialPutStr("\r\n Start Rpi08_0 Timer \r\n")	;
	set_vector_table();

	m_serialPutStr("Start TimerIRQ_x01_ Main\r\n");

	//m_serialPutStr("SCTLR (in Main1) = 0x%08x\r\n",readSCTLR());
	//printf("VectorBaseRegister (in Main1) = 0x%08x\r\n",readVectorBaseRegister());
	//m_serialPutStr("CPSR (in Main1) = 0x%08x\r\n",getmode());
	//printf("CPSR (in Main00) = 0x%08x\r\n",getmode());
	xval = getmode();
	m_serialPutStr("CPSR (in Main1) = 0x");
	itoaxval0((unsigned long)xval,&xvalC[0]);
	m_serialPutStr(&xvalC[0]);
	m_serialPutStr("\r\n");
	m_serialPutStr("CPSR (in Main2) = 0x");
	putxval0((unsigned long)xval,16);
	m_serialPutStr("\r\n");
	writeVectorBaseRegister(0x0000);
	setLowVector();
	//setHighVector();
	//printf("VectorBaseRegister (in Main2) = 0x%08x\r\n",readVectorBaseRegister());
	//printf("CPSR (in Main2) = 0x%08x\r\n",getmode());

//	Timer_initialize
//	 Disable all interrupts : void disable_all_IRQ(void)
	*INTERRUPT_DISABLE_BASIC_IRQS = 0xffffffff;
	*INTERRUPT_DISABLE_IRQS1 = 0xffffffff;
	*INTERRUPT_DISABLE_IRQS2 = 0xffffffff;
	*INTERRUPT_FIQ_CTRL = 0;
	disable_IRQ();

//	Timer_initialize :    Timer_initialize(unsigned int period)
	// Enable Timer-Interrupt
	*INTERRUPT_ENABLE_BASIC_IRQS = 0x01;

	// Stop Timer for setting
	*TIMER_CONTROL &= 0xffffff00;

	// Set Timer clock=1Mhz
	//（0xF9=249: timer clock=250MHz/(249+1)）
	*TIMER_PREDIVIDER = 0x000000F9;

	// Set Timer 4secs
	*TIMER_LOAD = 4000000-1;
	*TIMER_RELOAD = 4000000-1;

	// Clear Timer-Interrupt flag
	*TIMER_IRQ_CLR = 0;

	// Start timer
	// Timer enable, 32bit Timer
	*TIMER_CONTROL |= 0x000000A2;

	// Enable Timer-Interrupt
	*INTERRUPT_ENABLE_BASIC_IRQS = 0x01;

	// Enable IRQ
	enable_IRQ();
	//m_serialPutStr("CPSR (in Main3) = 0x%08x\r\n",getmode());
  rcvChar = m_serialGetChar();
 
m_serialPutStr(" Char=")	;
     m_serialPutChar(rcvChar);
        m_serialPutChar('\r');
        m_serialPutChar('\n');
        m_serialPutChar('>');
    while (rcvChar != 'q')
    {
        /* Wait for an incoming character. */
        rcvChar = m_serialGetChar();
	m_serialPutStr("\r\n Read m_serialGetChar \r\n")	;
        /* Echo the character back along with a carriage return and line feed. */
        m_serialPutChar(rcvChar);
        m_serialPutChar('\r');
        m_serialPutChar('\n');
        m_serialPutChar('>');
	delay(200);
    }
	m_serialPutStr("\r\n Progrm End \r\n")	;
    return 0;
}

//***********************************************************************/
//*	GNU Linker .text/.bss Initialize routine before main function.	*/
//***********************************************************************/

extern char etext[], sdata[], edata[], sbss[] , ebss[];
void initializeMemory()   // Memoru clear called from starup10.s
{
	char *src, *dst;
	
	for( src = etext, dst = sdata ; dst< edata ; )  // Initial data copy
		*dst++ = *src++;
		
	for( dst=sbss                 ; dst< ebss  ; )   // Bss 0 clead
		*dst++ =0;

}

