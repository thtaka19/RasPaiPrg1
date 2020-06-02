
#include <stdio.h>
#include <stdint.h>
#define CYCLES_PER_MS               (3000) // 2017 05

#define LED_GREEN16   		(0x01 << 16) 	// Port16(10+6)
void clearBss(void);

//void m_serialPutStr(char const *pOutputStr)
void serialPutStrXXX(char const *pOutputStr)
{
    char const *pChar;
    /* Send each character of the string. */
    for (pChar = pOutputStr; *pChar != '\0'; pChar++)
        m_serialPutChar(*pChar);

} 

void delay_ms00(int milliseconds)
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
void delay(int milliseconds){ delay_ms00( milliseconds);}

int main(void){
	disableInstructionCache();
	disableDataCache();
	disableMMU();


	// disable interrupt(IRQ)
	//	disable_all_IRQ();
	interruptDisable();
	// Set vectortable
	
	ledInit();
	ledOn(LED_GREEN16);

	// Enable UART1(mini_UART) 
	m_serialInit();

	m_serialPutStr("Start Main Rpi00_0 Pai3 Main V11\r\n");

	printf("\r\n Type EchoBack Characerr\n");
	while(1){
	 char rcvc;

	  rcvc=m_serialGetChar();
	  m_serialPutChar(rcvc);

 	  delay_ms00(10);
	}
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

void interruptServiceRoutine(void) { ///// Dummy for Interrupt called from startup10.s

}

