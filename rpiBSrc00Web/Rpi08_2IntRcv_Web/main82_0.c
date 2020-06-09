/************************************************************************/
/*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
/*      This is Free Software.   You can redistribute this software     */
/*      and/or modify it ,under the terms of the GNU General Public     */
/*      License version 3, or (at your option) any later version.       */
/*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
/************************************************************************/
#define HIGH	1
#define LOW		0

//#include "printf.h"
#include "led.h"
#include "mini_serial9Pls.h"
#include "startupAss.h"
#include "atoix_itoa.h"
#include "rpi_timer9.h"
#define CYCLES_PER_MS               (10000) // 2017 05
//void	disableInterrupt(void);
//void	enableInterrupt(void);
void    set_vector_table(void);
void    prt_vector_table(void);


int	getChar(void),m_serialGetChar();
void	putChar(int ),putChar0(),m_serialPutChar();
void	pie(void),pi(),e(),adc(),gpio();

void	initializeARM(void) ;
void	initializeHardware();
void	initializeCPU(void);
void	initializeBoardLED(void);
//void	initializeUART(void);
//void	initializeTimer(void);
void	initializeInterrupt(void);
void	initializeJtagPin(void);

void	initializeI2C(void) ;
void	initializeSPI(void) ;
void	initializeGPIO(void) ;

/***  #include "startupAss.h"
void 	interruptDisable(void);
void 	interruptEnable(void);
void	setLowVector(void);		// setLowVector();
void	disableDataCache(void);
void	disableInstructionCache(void);

void	writeVectorBaseRegister(void(*)(void));
***/

volatile	int	timer0;


void m_serialPutStrI(char const *pOutputStr)
{
    char const *pChar;
    /* Send each character of the string. */
    for (pChar = pOutputStr; *pChar != '\0'; pChar++)
        m_serialPutCharI(*pChar);//m_serialPutChar
} 
void delay(int milliseconds)
{
    long volatile cycles = milliseconds;
	int volatile  cycle0 = CYCLES_PER_MS;
     
    while (cycles != 0) {
        cycles--;
		cycle0 = CYCLES_PER_MS;
	  while(cycle0 != 0)
		  cycle0--;
	}
}

int	main(void )
{
	int putData[128] ;
	static int	n=0;
	int rcvChar,i1,i2 ;
	int     irqP[3],rcvSndI[3];
//m_serialPutChar('A');// Not work

	// Disablr IRQ

	interruptDisable();

	initializeHardware();
//	serialInit();// No Interrupt
	m_serialInitIrcv();// receive Interrupt : mini_serial9AdI.c

	ledInit();


//	m_serialPutChar('C');// Debug
	set_vector_table();
	writeVectorBaseRegister(0x0000);
	setLowVector();//setLowVector();	

	interruptEnable();

	delay(10);
	m_serialPutStr("\r\n\nStart 08_2 Sereal Receve  Interrupt main v05 Origin001\r\n");
	prt_vector_table();

	rcvChar = m_serialGetCharI();// Interrupt get Char
	while(rcvChar > 0) { // Sweep out 
	  m_serialPutChar(rcvChar);

	  rcvChar = m_serialGetCharI();
        }
	printf("\nWelcome to ARM Common Software (%s %s).\r\n", __DATE__ , __TIME__);
	printf("08_2   only Rcv serial Interrupt. Send(Trancefer) serial and Timer  are not Interrupt.\r\n");
	printf("Please type key-Board.\r\n");
	printf("Program read serial every 200ms. counter i1.if No Key-in return\r\n");
	printf("When key-In Interrupt occer and '+' come.\r\n");
	printf("During 200ms Key-In Charcters will print same time.\r\n");
        i1=i2=0;
 		irqPcnt(irqP);
  		rcvSndIcnt(rcvSndI) ;
		printf("\r\nStart: Timer Int = %d ;  mini_Uart Int = %d\r\n",irqP[0],irqP[1]);
		printf("Start: mini_Uart Rcv Int = %d ; Snd empty Int = %d( Real Snd =%d )\r\n",rcvSndI[0],rcvSndI[1],rcvSndI[2]);
	m_serialPutStr("\r\n\nPlease Key-in many times\r\n");

	while(1) {
		delay(200);

//		printf("\n%8d\ttime=\t%16d\n",++n,timer);
		rcvChar = m_serialGetCharI();// Interrupt get Char
		i1++;

		while(rcvChar > 0) {
		  i2++;
	 	  m_serialPutChar(rcvChar);

		  rcvChar = m_serialGetCharI();//
		  i1++;
 
        	}
// 		m_serialPutChar('*');// Debug
                if(i1%50 ==0) {
                printf("\r\n\r\n10sec-Message :  m_getCharI try =%d times.And real get Char=%d times. \r\n",i1,i2);
 irqPcnt(irqP);
  rcvSndIcnt(rcvSndI) ;
		printf("Timer Int = %d ;  mini_Uart Int = %d\r\n",irqP[0],irqP[1]);
		printf("mini_Uart Rcv Int = %d ; Snd emptyInt = %d ( Real Snd =%d )\r\n",rcvSndI[0],rcvSndI[1],rcvSndI[2]);
		}

	}// While(1) END
}


void initializeHardware() {

//	interruptDisable();
	disable_IRQ();
	initializeARM();
//	initializeJtagPin();	// Only for Raspberry PI  move to crt0.s
//	initializeCPU();
//	initializeBoardLED();
//	initializeUART();	// initialize RS232C serial port (115200bps)
//	serialInit();
//	initializeI2C();	// initialize I2C serial port
//	initializeSPI();	// initialize SPI serial port
//	initializeGPIO();	// initialize GPIO serial port
//	initializeTimer();	// 	set timer_Interrupt Timer
//	timerInit();
}

//***********************************************************************/
//*	GNU Linker .text/.bss Initialize routine before main function.	*/
//***********************************************************************/

extern char etext[], sdata[], edata[], sbss[] , ebss[];

void initializeMemory()
{
	char *src, *dst;
	
	for( src = etext, dst = sdata ; dst< edata ; ) 
		*dst++ = *src++;
		
	for( dst=sbss                 ; dst< ebss  ; ) 
		*dst++ =0;

}


//***********************************************************************/
//*	ARM Architecture Dependent Code					*/
//***********************************************************************/


//#if	!defined(AARCH64) && !defined(AARCH32T)
//***********************************************************************/
//*	ARMv4T / ARMv5T / ARMv6 / ARMv7-A (Original Basic Architecture)	*/
//*	32bit ARM	ARM7 / ARM9 / ARM11 / Cortex-A7/A8/A9 seriese	*/
//***********************************************************************/

void	setLowVector(void);		// setHighVector();
void	disableDataCache(void);
void	disableInstructionCache(void);


void initializeARM() {

	setLowVector();		// setHighVector();
//	writeVectorBaseRegister(instructionTable);//  TT
	writeVectorBaseRegister(0x0000);//TT
	disableDataCache();
	disableInstructionCache();

}
//#endif

